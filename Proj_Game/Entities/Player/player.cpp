#include "player.h"

#define P1_TEXTURE_REF "Resources/characters/player/sheets/DinoSprites_mort.png"
#define P2_TEXTURE_REF "Resources/characters/player/sheets/DinoSprites_vita.png"

#define INVENCIBILITY_FRAMES_TIME 2.5f

#define H_ACCELERATION 0.6f
#define H_MAX_ACCELERATION 0.3f

#define JUMP -0.5f
#define V_ACCELERATION 1.f
#define V_MAX_ACCELERATION 0.75f

#define PLAYER_TOTAL_LIFE 10U

unsigned int Characters::Player::playerCounter = 0;

Characters::Player::Player():
	Character(Ente::CHARACTER, sf::RectangleShape(sf::Vector2f(24.f, 24.f)), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(24, 24)), std::string(), PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME),
	onGround(true), crouching(false), jump(false), walkLeft(false), walkRight(false), walking(true), done(false), playerId(playerCounter)
{
	playerCounter++;

	if(playerCounter == 1)
		this->texture.loadFromFile(P1_TEXTURE_REF);
	else
		this->texture.loadFromFile(P2_TEXTURE_REF);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
#endif
};
Characters::Player::~Player()
{
	playerCounter--;
};

void Characters::Player::PlayerInputHandler(const sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::D:
			if (this->playerId == 0)
				this->walkRight = true;
			break;
		case sf::Keyboard::A:
			if (this->playerId == 0)
				this->walkLeft = true;
			break;
		case sf::Keyboard::W:
			if (this->playerId == 0)
				this->jump = true;
			break;
		case sf::Keyboard::S:
			if (this->playerId == 0)
				this->crouching = true;
			break;
		case sf::Keyboard::Right:
			if (this->playerId == 1)
				this->walkRight = true;
			break;
		case sf::Keyboard::Left:
			if (this->playerId == 1)
				this->walkLeft = true;
			break;
		case sf::Keyboard::Up:
			if (this->playerId == 1)
				this->jump = true;
			break;
		case sf::Keyboard::Down:
			if (this->playerId == 1)
				this->crouching = true;
			break;
		case sf::Keyboard::Enter:
			if (!this->done)
			{
				if (this->walking)
					this->walking = false;
				else
					this->walking = true;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::D:
			if (this->playerId == 0)
				this->walkRight = false;
			break;
		case sf::Keyboard::A:
			if (this->playerId == 0)
				this->walkLeft = false;
			break;
		case sf::Keyboard::W:
			if (this->playerId == 0)
				this->jump = false;
			break;
		case sf::Keyboard::S:
			if (this->playerId == 0)
				this->crouching = false;
			break;
		case sf::Keyboard::Right:
			if (this->playerId == 1)
				this->walkRight = false;
			break;
		case sf::Keyboard::Left:
			if (this->playerId == 1)
				this->walkLeft = false;
			break;
		case sf::Keyboard::Up:
			if (this->playerId == 1)
				this->jump = false;
			break;
		case sf::Keyboard::Down:
			if (this->playerId == 1)
				this->crouching = false;
			break;
		default:
			break;
		}
	}
};
void Characters::Player::Execute(const float elapsedTime)
{
	float coeff = H_ACCELERATION * elapsedTime;

	if (this->walking)
	{
		if (this->jump && this->onGround && !this->crouching)
		{
			this->onGround = false;
			this->speedV += JUMP;
			coeff /= 10;
		}

		if ((this->walkLeft && !this->walkRight) || (!this->walkLeft && this->walkRight))
		{
			if (this->walkRight && this->speedH < H_MAX_ACCELERATION)
				this->speedH += coeff;

			if (this->walkLeft && this->speedH > -H_MAX_ACCELERATION)
				this->speedH -= coeff;
		}
		else
		{
			if (this->speedH < 0.f)
				this->speedH += coeff;

			if (this->speedH > 0.f)
				this->speedH -= coeff;

			if (this->speedH <= 0.1f && this->speedH >= -0.1f)
				this->speedH = 0.f;
		}

		/*if(this->crouching)
			speedH = 0;*/

		if (!this->onGround)
		{
			if (speedV < V_MAX_ACCELERATION)
				speedV += V_ACCELERATION * elapsedTime;
		}
		else
			speedV = 0;
	}
	else
	{
		if ((this->walkLeft && !this->walkRight) || (!this->walkLeft && this->walkRight))
		{
			if (this->walkRight && this->speedH < H_MAX_ACCELERATION)
				this->speedH += coeff;

			if (this->walkLeft && this->speedH > -H_MAX_ACCELERATION)
				this->speedH -= coeff;
		}
		else
		{
			if (this->speedH < 0.f)
				this->speedH += coeff;

			if (this->speedH > 0.f)
				this->speedH -= coeff;

			if (this->speedH <= 0.1f && this->speedH >= -0.1f)
				this->speedH = 0.f;
		}
		if ((this->jump && !this->crouching) || (!this->jump && this->crouching))
		{
			if (this->jump && this->speedV < H_MAX_ACCELERATION)
				this->speedV -= coeff;

			if (this->crouching && this->speedV > -H_MAX_ACCELERATION)
				this->speedV += coeff;
		}
		else
		{
			if (this->speedV < 0.f)
				this->speedV += coeff;

			if (this->speedV > 0.f)
				this->speedV -= coeff;

			if (this->speedV <= 0.1f && this->speedV >= -0.1f)
				this->speedV = 0.f;
		}
	}

	this->MovePosition(sf::Vector2f(speedH, speedV));
};
void Characters::Player::SelfPrint(sf::RenderWindow& context_window, const float elapsedTime)
{
	context_window.draw(this->hitBox);
	context_window.draw(this->body);
};
void Characters::Player::Collided(const int type, const sf::Vector2f& movement)
{
	if(type == Ente::OBSTACLE || type == Ente::CAMERA)
	{
		
	}
	if (type == Ente::PROJECTILE || type == Ente::ENEMY)
	{

	}
};