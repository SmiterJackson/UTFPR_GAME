#include "player.h"
#include "../game/game.h"
using namespace Trait;
using namespace Characters;

#define P1_TEXTURE_REF "Proj_Game/Resources/characters/player/sheets/DinoSprites_mort.png"
#define P2_TEXTURE_REF "Proj_Game/Resources/characters/player/sheets/DinoSprites_vita.png"

#define TEXTURE_TOKEN_SIZE 24

#define INVENCIBILITY_FRAMES_TIME 2.5f

#define H_ACCELERATION 0.6f
#define H_MAX_ACCELERATION 0.3f

#define JUMP -0.5f
#define V_ACCELERATION 1.f
#define V_MAX_ACCELERATION (JUMP * -1.5f)

#define HITBOX sf::Vector2f(18.f, 18.f)

#define PLAYER_TOTAL_LIFE 10U

std::list<Player*> Player::playerList = std::list<Player*>();

Player::Player(float size_proportion) :
	Character(
		Type::PLAYER, HITBOX, sf::Vector2f(0.f, 0.f), std::string(),
		AnimationSheet(), PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME, false, size_proportion
	),
	Observer(this->id),
	onGround(false), crouching(false), jump(false), 
	walkLeft(false), walkRight(false), walking(true), done(false), 
	playerId(playerList.size())
{
	playerList.emplace_back(this);

	if (playerList.size() == 1)
		this->SetTexture(P1_TEXTURE_REF, sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE));
	else
		this->SetTexture(P2_TEXTURE_REF, sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE));

	sf::Vector2i size(TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE);
	this->AddRangeAnimations(
		std::vector<std::pair<int, Animation>>(
			{
			std::pair<int, Animation>(Actions::IDLE,		Animation(0, 2, 0,		size, 0.4f,		true)),
			std::pair<int, Animation>(Actions::WALKING,		Animation(3, 9, 0,		size, 0.15f,	true)),
			std::pair<int, Animation>(Actions::KICK,		Animation(10, 12, 0,	size, 0.6f,		true)),
			std::pair<int, Animation>(Actions::DAMAGED,		Animation(13, 16, 0,	size, 0.6f,		true)),
			std::pair<int, Animation>(Actions::CROUCHING,	Animation(17, 23, 0,	size, 0.1f,		true))
			}
		)
	);
};
Player::~Player()
{
	std::list<Player*>::iterator it;

	for(it = playerList.begin(); it != playerList.end(); it++)
	{
		if((*it)->GetPlayerId() == this->playerId)
		{
			playerList.erase(it);
			break;
		}
	}
};

void Player::UpdateObsever(const sf::Event& _event)
{
	if (Game::GetGameState() == GameStateType::IN_GAME && _event.type == sf::Event::KeyPressed)
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
	else if(Game::GetGameState() == GameStateType::IN_GAME && _event.type == sf::Event::KeyReleased)
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
void Player::Execute(const float& pElapsedTime)
{
	float coeff = H_ACCELERATION * pElapsedTime;

	if (this->walking)
	{
		if (this->jump && this->onGround && !this->crouching)
		{
			this->onGround = false;
			this->speedV = JUMP;
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

		if (!this->onGround)
		{
			if (this->speedV < V_MAX_ACCELERATION)
				this->speedV += V_ACCELERATION * pElapsedTime;
		}
		else
		{
			this->speedV = 0.f;
			this->onGround = false;
		}
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

	this->MovePosition(sf::Vector2f(this->speedH, this->speedV));

#ifdef _DEBUG
	this->origin.setPosition(this->hitBox.getPosition());
#endif
};

void Player::InCollision(Entity* _other, const sf::Vector2f& intersection)
{
	sf::Vector2f distance(
		_other->GetPosition().x - this->GetPosition().x,
		_other->GetPosition().y - this->GetPosition().y
	);

	if (intersection.y >= intersection.x)
	{
		if (distance.y > 0.f)
		{
			this->MovePosition(0.f, (intersection.y));
				this->onGround = true;
		}
		else
		{
			this->MovePosition(0.f, -(intersection.y));
			this->speedV = 0.f;
		}
	}
	else
	{
		if (distance.x > 0.f)
			this->MovePosition(intersection.x, 0.f);
		else
			this->MovePosition(-(intersection.x), 0.f);
	}
};
void Player::OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
{
	sf::FloatRect bounds(this->GetBounds());
	sf::Vector2f offSet(0.f, 0.f);

	if (colType == CollisionType::MapColl)
	{
		if (bounds.top < ofBounds.top)
			offSet.y += ofBounds.top - bounds.top;
		else if (bounds.height > ofBounds.height)
		{
			offSet.y += ofBounds.height - bounds.height;
			this->onGround = true;
		}
	}

	if (bounds.left < ofBounds.left)
	{
		this->speedH = 0.f;
		offSet.x += ofBounds.left - bounds.left;
	}
	else if (bounds.width > ofBounds.width)
	{
		this->speedH = 0.f;
		offSet.x += ofBounds.width - bounds.width;
	}

	this->MovePosition(offSet);
};