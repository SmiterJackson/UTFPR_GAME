#include "player.h"
#include "../game/game.h"
#include "../Entes/GUI/Interfaces/Stage/stage.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Trait;
using namespace Manager;
using namespace Characters;

#define P1_TEXTURE_REF "Proj_Game/Resources/characters/player/Colour1/spritesheet.png"
#define P2_TEXTURE_REF "Proj_Game/Resources/characters/player/Colour2/spritesheet.png"

#define TOKEN_SIZE sf::Vector2i(120, 80)
#define HITBOX sf::Vector2f(25.f, 38.f)
#define SIZE_COEFF 1.0f

#define INVENCIBILITY_FRAMES_TIME 2.5f
#define PLAYER_TOTAL_LIFE 10U

#define H_ACCELERATION 10.f
#define H_MAX_ACCELERATION 2.8f

#define JUMP_SPEED -6.5f

std::list<Player*>									Player::playerList = std::list<Player*>();
std::vector<std::pair<int, Animated::Animation>>	Player::playersAnimations = {
	std::pair<int, Animation>(Actions::IDLE,			Animation(0, 9,		1, TOKEN_SIZE, 0.2f, true)),
	std::pair<int, Animation>(Actions::IDLE_CROUCH,		Animation(8, 8,		3, TOKEN_SIZE, 1.f, false)),
	std::pair<int, Animation>(Actions::WALK,			Animation(0, 9,		2, TOKEN_SIZE, 0.125f, true)),
	std::pair<int, Animation>(Actions::WALK_CROUCH,		Animation(0, 7,		3, TOKEN_SIZE, 0.15f, true)),
	std::pair<int, Animation>(Actions::ATTACK,			Animation(0, 5,		4, TOKEN_SIZE, 0.5f, false)),
	std::pair<int, Animation>(Actions::ATTACK_CROUCH,	Animation(6, 9,		4, TOKEN_SIZE, 0.5f, false)),
	std::pair<int, Animation>(Actions::JUMP,			Animation(3, 5,		5, TOKEN_SIZE, 0.1f, false)),
	std::pair<int, Animation>(Actions::FALL,			Animation(0, 2,		5, TOKEN_SIZE, 0.1f, false)),
	std::pair<int, Animation>(Actions::DAMAGED,			Animation(9, 9,		3, TOKEN_SIZE, 0.5f, false)),
	std::pair<int, Animation>(Actions::DIED,			Animation(0, 9,		0, TOKEN_SIZE, 0.5f, false))
};

Player::Player() :
	Character(
		Type::PLAYER, HITBOX, sf::Vector2f(0.f, 0.f), (playerList.size() == 0 ? P1_TEXTURE_REF : P2_TEXTURE_REF),
		playersAnimations, PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME, 1.f, false, SIZE_COEFF
	),
	Observer(this->id),
	keyToActions(Player::GetKeyMap(playerList.size())),
	shorter(false), onGround(false), crouching(false), jump(false),
	walkLeft(false), walkRight(false)
{
	playerList.emplace_back(this);
	this->body.setOrigin(this->body.getOrigin() + sf::Vector2f(0.f, 21.f));
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
		case ActionMap::JUMPED:
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
		case ActionMap::JUMPED:
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
void Player::SelfPrint()
{
	this->UpdateAnimation(elapsedTime);
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->originCircle);
#endif
};
void Player::Execute()
{
	this->Move();

#ifdef _DEBUG
	this->originCircle.setPosition(this->hitBox.getPosition());
#endif
};

void Player::Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType)
{
	sf::Vector2f move(0.f, 0.f);

	if (colType == CollisionType::MapColl)
	{
		if (intersection.y < 0.f)
			this->onGround = true;

		move = intersection;
	}
	else if (colType == CollisionType::CameraColl)
	{
		move = sf::Vector2f(intersection.x , 0.f);
	}
	else if (_other != nullptr)
		move = this->EntityCollision(_other, intersection);

	this->MovePosition(move.x, move.y);
};
const sf::Vector2f Player::EntityCollision(const Entity* other, const sf::Vector2f& intersection)
{
	sf::Vector2f movDist;
	sf::Vector2f distance(
		other->GetPosition().x - this->GetPosition().x,
		other->GetPosition().y - this->GetPosition().y
	);

	if (other->GetType() == Type::OBSTACLE)
	{
		if (intersection.y >= intersection.x)
		{
			if (distance.y > 0.f)
			{
				movDist = sf::Vector2f(0.f, (intersection.y));
				this->onGround = true;
			}
			else
			{
				movDist = sf::Vector2f(0.f, -(intersection.y));
				this->speedV = 0.f;
			}
		}
		else
		{
			if (distance.x > 0.f)
				movDist = sf::Vector2f((intersection.x), 0.f);
			else
				movDist = sf::Vector2f(-(intersection.x), 0.f);
		}
	}
	else if (other->GetType() == Type::ENEMY || other->GetType() == Type::PROJECTILE)
	{

	}

	return movDist;
};

void Player::Attack()
{

};
void Player::Move()
{
	float coeff = H_ACCELERATION * elapsedTime * this->speedCoeff;
	float hLim = H_MAX_ACCELERATION;

	if (this->crouching)
	{
		if (!this->shorter)
		{
			this->SetHitBoxSize(HITBOX - sf::Vector2f(0.f, HITBOX.y / 2.f));
			this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
			this->hitBox.setPosition(this->body.getPosition() + sf::Vector2f(0.f, HITBOX.y / 4.f));

			this->shorter = true;
		}

		hLim /= 2.f;
		if (this->speedH >= hLim)
			this->speedH = hLim;

		if (this->speedH <= -hLim)
			this->speedH = -hLim;
	}
	else
	{
		this->shorter = false;
		this->SetHitBoxSize(HITBOX);
		this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
		this->hitBox.setPosition(this->body.getPosition());
	}

	if ((this->walkLeft && !this->walkRight) || (!this->walkLeft && this->walkRight))
	{
		if (this->walkRight && this->speedH < hLim)
			this->speedH += coeff;

		if (this->walkLeft && this->speedH > -hLim)
			this->speedH -= coeff;


		if (this->crouching)
			this->next_ani = Actions::WALK_CROUCH;
		else
			this->next_ani = Actions::WALK;
	}
	else
	{
		if (this->speedH < 0.f)
			this->speedH += coeff;

		if (this->speedH > 0.f)
			this->speedH -= coeff;

		if (this->speedH <= 0.2f && this->speedH >= -0.2f)
			this->speedH = 0.f;


		if (this->crouching)
			this->next_ani = Actions::IDLE_CROUCH;
		else
			this->next_ani = Actions::IDLE;
	}

	if (this->jump && this->onGround && !this->crouching)
	{
		this->next_ani = Actions::JUMP;

		this->onGround = false;
		this->speedV = JUMP_SPEED;
		coeff /= 10;
	}

	if (!this->onGround)
	{
		if (this->speedV < 0.f)
			this->next_ani = Actions::JUMP;
		else if (this->speedV > 0.f)
			this->next_ani = Actions::FALL;

		if (this->speedV < maxGravityPull)
			this->speedV += gravity * elapsedTime;
	}
	else
	{
		this->speedV = 0.f;
		this->onGround = false;
	}

	this->MovePosition(this->speedH, this->speedV);
};
void Player::Died()
{
	
};

Player::keyToAction Player::GetKeyMap(unsigned int size)
{
	typedef Player::keyToAction::value_type Value;

	const Player::keyToAction player_1_ActionsMap = {
		Value(sf::Keyboard::D,		Player::ActionMap::WALK_RIGHT),
		Value(sf::Keyboard::A,		Player::ActionMap::WALK_LEFT),
		Value(sf::Keyboard::W,		Player::ActionMap::JUMPED),
		Value(sf::Keyboard::S,		Player::ActionMap::CROUCH)
	};
	const Player::keyToAction player_2_ActionsMap = {
		Value(sf::Keyboard::Right,	Player::ActionMap::WALK_RIGHT),
		Value(sf::Keyboard::Left,	Player::ActionMap::WALK_LEFT),
		Value(sf::Keyboard::Up,		Player::ActionMap::JUMPED),
		Value(sf::Keyboard::Down,	Player::ActionMap::CROUCH)
	};

	if (size == 1)
		return player_2_ActionsMap;

	return player_1_ActionsMap;
};