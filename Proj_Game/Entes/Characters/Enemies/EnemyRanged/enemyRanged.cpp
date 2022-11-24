#include "enemyRanged.h"
using namespace Enemies;
using namespace Trait;

#define PATH "Proj_Game/Resources/characters/arcaneArcher/spritesheet.png"
#define TOKEN_SIZE sf::Vector2i(64, 64)

#define SWITCHTIME 3.f

#define HITBOX_SIZE sf::Vector2f(26.f, 33.f)

std::vector<std::pair<int, Animated::Animation>> EnemyRanged::enemyAnimations = {
	std::pair<int, Animation>(Actions::IDLE,	Animation(0, 3,	5, TOKEN_SIZE, 0.27f, true)),
	std::pair<int, Animation>(Actions::RUN,		Animation(0, 7,	0, TOKEN_SIZE, 0.165f, true)),
	std::pair<int, Animation>(Actions::SHOOT,	Animation(0, 6,	3, TOKEN_SIZE, 0.13f, true)),
	std::pair<int, Animation>(Actions::JUMP,	Animation(0, 0,	7, TOKEN_SIZE, 1.f, false)),
	std::pair<int, Animation>(Actions::FALL,	Animation(1, 1,	7, TOKEN_SIZE, 1.f, false)),
	std::pair<int, Animation>(Actions::ROLL,	Animation(0, 6,	2, TOKEN_SIZE, 0.145f, true)),
	std::pair<int, Animation>(Actions::DIED,	Animation(0, 7,	1, TOKEN_SIZE, 0.175f, true))
};

EnemyRanged::EnemyRanged():
	Enemy(
		HITBOX_SIZE, sf::Vector2f(0.f, 0.f), PATH,
		enemyAnimations, 10, 0.1f, 3.f, 200.f, false, 1.f
	),
	acumml(0.f), action(0)
{};
EnemyRanged::~EnemyRanged()
{};

void EnemyRanged::Execute()
{
	this->acumml += elapsedTime;

	if (this->acumml >= SWITCHTIME)
	{
		this->acumml -= SWITCHTIME;

		this->action++;

		if (this->action > Actions::DIED)
			this->action = Actions::IDLE;
	}

	this->next_ani = this->action;
};
void EnemyRanged::Attack()
{

};
void EnemyRanged::Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType)
{

};
void EnemyRanged::Died()
{

};