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
	Character(
		Instance::CHARACTER, sf::RectangleShape(sf::Vector2f(0.f, 0.f)), nullptr, std::string(),
		std::vector<std::pair<int, Animation>>(), sf::IntRect(0, 0, 24, 24), PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME
	),
	onGround(true), crouching(false), jump(false), walkLeft(false), walkRight(false), walking(true), done(false), playerId(playerCounter)
{
	Initialize();
};
Characters::Player::Player(float* elapsed_timeRef):
	Character(
		Instance::CHARACTER, sf::RectangleShape(sf::Vector2f(15.f, 18.f)), elapsed_timeRef, std::string(),
		std::list<std::pair<int, Animation>>(), sf::IntRect(0, 0, 0, 0),  PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME
	),
	onGround(true), crouching(false), jump(false), walkLeft(false), walkRight(false), walking(true), done(false), playerId(playerCounter)
{
	Initialize();
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
			{
				this->walkRight = true;
				this->looking_right = true;
			}
			break;
		case sf::Keyboard::A:
			if (this->playerId == 0)
			{
				this->walkLeft = true;
				this->looking_right = false;
			}
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
			{
				this->walkRight = true;
				this->looking_right = true;
			}
			break;
		case sf::Keyboard::Left:
			if (this->playerId == 1)
			{
				this->walkLeft = true;
				this->looking_right = false;
			}
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
void Characters::Player::Initialize()
{
	this->playerCounter++;

	if (this->playerCounter == 1)
		this->SetTexture(P1_TEXTURE_REF, sf::IntRect(0, 0, 24, 24));
	else
		this->SetTexture(P2_TEXTURE_REF, sf::IntRect(0, 0, 24, 24));

	sf::Vector2i size(24, 24);
	this->AddRangeAnimations(
		std::vector<std::pair<int, Animation>>({
			std::pair<int, Animation>(Actions::IDLE,		Animation(0, 2, 0, size, 0.4f, true)),
			std::pair<int, Animation>(Actions::WALKING,		Animation(3, 9, 0, size, 0.15f, true)),
			std::pair<int, Animation>(Actions::KICK,		Animation(10, 12, 0, size, 0.6f, true)),
			std::pair<int, Animation>(Actions::DAMAGED,		Animation(13, 16, 0, size, 0.6f, true)),
			std::pair<int, Animation>(Actions::CROUCHING,	Animation(17, 23, 0, size, 0.1f, true))
			}
		)
	);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
#endif
};
void Characters::Player::Execute()
{
	float coeff = H_ACCELERATION * (*this->elapsed_time);

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
			if (!this->crouching)
				this->next_ani = Actions::WALKING;
			else
			{
				this->next_ani = Actions::CROUCHING;
				coeff /= 2.f;
			}

			if (this->walkRight && this->speedH < H_MAX_ACCELERATION)
				this->speedH += coeff;

			if (this->walkLeft && this->speedH > -H_MAX_ACCELERATION)
				this->speedH -= coeff;
		}
		else
		{
			this->next_ani = Actions::IDLE;

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
				speedV += V_ACCELERATION * (*this->elapsed_time);
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
void Characters::Player::SelfPrint(sf::RenderWindow& context_window)
{
	if (this->next_ani != this->last_ani)
	{
		this->animations[this->last_ani].ResetAnimation();
		this->last_ani = this->next_ani;
	}

	this->body.setTextureRect(this->animations[this->next_ani].update(this->elapsed_time, this->looking_right));
	context_window.draw(this->body);
	context_window.draw(this->hitBox);
};
void Characters::Player::Collided(const int type, const sf::Vector2f& movement)
{
	switch (type)
	{
	case Instance::CAMERA:
		break;
	case Instance::OBSTACLE:
		break;
	case Instance::PROJECTILE:
		break;
	case Instance::ENEMY:
		break;
	default:
		break;
	}
};