#include "player.h"
#include "../game/game.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Trait;
using namespace Manager;
using namespace Characters;

#define P1_TEXTURE_REF "Proj_Game/Resources/characters/player/sheets/DinoSprites_mort.png"
#define P2_TEXTURE_REF "Proj_Game/Resources/characters/player/sheets/DinoSprites_vita.png"

#define TEXTURE_TOKEN_SIZE sf::Vector2i(24, 24)
#define HITBOX sf::Vector2f(18.f, 18.f)
#define SIZE_COEFF 1.0f

#define INVENCIBILITY_FRAMES_TIME 2.5f
#define PLAYER_TOTAL_LIFE 10U

#define H_ACCELERATION 0.6f
#define H_MAX_ACCELERATION 0.3f

#define JUMP_SPEED -0.5f
#define V_ACCELERATION 1.f
#define V_MAX_ACCELERATION (JUMP_SPEED * -1.5f)

std::list<Player*>									Player::playerList = std::list<Player*>();
std::vector<std::pair<int, Animated::Animation>>	Player::playersAnimations = {
	std::pair<int, Animation>(Actions::IDLE,		Animation(0, 2, 0, TEXTURE_TOKEN_SIZE, 0.4f, true)),
	std::pair<int, Animation>(Actions::WALKING,		Animation(3, 9, 0, TEXTURE_TOKEN_SIZE, 0.15f, true)),
	std::pair<int, Animation>(Actions::KICK,		Animation(10, 12, 0, TEXTURE_TOKEN_SIZE, 0.6f, true)),
	std::pair<int, Animation>(Actions::DAMAGED,		Animation(13, 16, 0, TEXTURE_TOKEN_SIZE, 0.6f, true)),
	std::pair<int, Animation>(Actions::CROUCHING,	Animation(17, 23, 0, TEXTURE_TOKEN_SIZE, 0.1f, true))
};

Player::Player() :
	Character(
		Type::PLAYER, HITBOX, sf::Vector2f(0.f, 0.f), (playerList.size() == 0 ? P1_TEXTURE_REF : P2_TEXTURE_REF),
		playersAnimations, PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME, false, SIZE_COEFF
	),
	Observer(this->id),
	keyToActions(Player::GetKeyMap(playerList.size())),
	onGround(false), crouching(false), jump(false), 
	walkLeft(false), walkRight(false)
{
	playerList.emplace_back(this);
};
Player::~Player()
{
	std::list<Player*>::iterator it;

	for(it = playerList.begin(); it != playerList.end(); it++)
	{
		if((*it)->GetId() == this->id)
		{
			playerList.erase(it);
			break;
		}
	}
};

void Player::UpdateObsever(const sf::Event& _event)
{
	keyToAction::iterator it(this->keyToActions.find(_event.key.code));
	if (it == this->keyToActions.end())
		return;

	if (_event.type == sf::Event::KeyPressed)
	{
		switch (it->second)
		{
		case ActionMap::WALK_RIGHT:
				this->walkRight = true;
				this->looking_right = true;
			break;
		case ActionMap::WALK_LEFT:
				this->walkLeft = true;
				this->looking_right = false;
			break;
		case ActionMap::JUMP:
				this->jump = true;
			break;
		case ActionMap::CROUCH:
				this->crouching = true;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (it->second)
		{
		case ActionMap::WALK_RIGHT:
				this->walkRight = false;
			break;
		case ActionMap::WALK_LEFT:
				this->walkLeft = false;
			break;
		case ActionMap::JUMP:
				this->jump = false;
			break;
		case ActionMap::CROUCH:
				this->crouching = false;
			break;
		default:
			break;
		}
	}
};
void Player::SelfPrint(const float& pElapsedTime)
{
	this->UpdateAnimation(pElapsedTime);
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->origin);
#endif
};
void Player::Execute(const float& pElapsedTime)
{
	float coeff = H_ACCELERATION * pElapsedTime * this->speedCoeff;

	if (this->jump && this->onGround && !this->crouching)
	{
		this->onGround = false;
		this->speedV = JUMP_SPEED;
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

Player::keyToAction Player::GetKeyMap(unsigned int size)
{
	typedef Player::keyToAction::value_type Value;

	const Player::keyToAction player_1_ActionsMap = {
		Value(sf::Keyboard::D,		Player::ActionMap::WALK_RIGHT),
		Value(sf::Keyboard::A,		Player::ActionMap::WALK_LEFT),
		Value(sf::Keyboard::W,		Player::ActionMap::JUMP),
		Value(sf::Keyboard::S,		Player::ActionMap::CROUCH)
	};
	const Player::keyToAction player_2_ActionsMap = {
		Value(sf::Keyboard::Right,	Player::ActionMap::WALK_RIGHT),
		Value(sf::Keyboard::Left,	Player::ActionMap::WALK_LEFT),
		Value(sf::Keyboard::Up,		Player::ActionMap::JUMP),
		Value(sf::Keyboard::Down,	Player::ActionMap::CROUCH)
	};

	if (size == 1)
		return player_2_ActionsMap;

	return player_1_ActionsMap;
};