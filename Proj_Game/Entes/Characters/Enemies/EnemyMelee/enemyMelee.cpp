#include "enemyMelee.h"
using namespace Enemies;
using namespace Trait;

#define PATH "Proj_Game/Resources/characters/skeletonEnemy/skeleton.png"
#define TOKEN_SIZE sf::Vector2i(64, 64)

#define SWITCHTIME 3.f

#define HITBOX_SIZE sf::Vector2f(26.f, 33.f)

std::vector<std::pair<int, Animated::Animation>> EnemyMelee::enemyAnimations = {
	std::pair<int, Animation>(Actions::IDLE,	Animation(0, 3, 3, TOKEN_SIZE, 0.27f, true)),
	std::pair<int, Animation>(Actions::WALK,	Animation(0, 11, 2, TOKEN_SIZE, 0.165f, true)),
	std::pair<int, Animation>(Actions::ATTACK,	Animation(0, 12, 0, TOKEN_SIZE, 0.13f, true)),
	std::pair<int, Animation>(Actions::DAMAGED,	Animation(0, 2, 4, TOKEN_SIZE, 0.2f, true)),
	std::pair<int, Animation>(Actions::DIED,	Animation(0, 12, 1, TOKEN_SIZE, 0.2f, true))
};

EnemyMelee::EnemyMelee():
	Enemy(
		HITBOX_SIZE, sf::Vector2f(0.f, 0.f), PATH,
		enemyAnimations, 10, 0.1f, 3.f, 200.f, false, 1.f
	),
	acumml(0.f), action(0), roled(true)
{};
EnemyMelee::~EnemyMelee()
{};

void EnemyMelee::Execute()
{
	this->acumml += elapsedTime;

	if(this->acumml >= SWITCHTIME)
	{
		this->acumml -= SWITCHTIME;

		this->action++;

		if (this->action > Actions::DIED)
			this->action = Actions::IDLE;

		this->roled = false;
	}

	this->next_ani = this->action;

	if (!this->roled)
	{
		this->AStarAlgorithm(this->GetPosition());
		this->roled = true;
	}
};
void EnemyMelee::Attack()
{};
void EnemyMelee::Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType)
{
	
};
void EnemyMelee::Died()
{
	
};