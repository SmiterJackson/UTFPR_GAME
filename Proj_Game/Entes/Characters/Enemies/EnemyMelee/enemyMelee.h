#pragma once

#include "../Enemy/enemy.h"

namespace Enemies
{
	class EnemyMelee : public Enemy
	{
	private:
		enum Actions
		{
			IDLE = 0,
			WALK,
			ATTACK,
			DAMAGED,
			DIED
		};

	public:
		EnemyMelee();
		~EnemyMelee();

		virtual void Execute();
		virtual void Attack();
		virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType);

	protected:
		virtual void Died();

	protected:
		static std::vector<std::pair<int, Animated::Animation>> enemyAnimations;
		float acumml;
		unsigned int action;
		bool roled;
	};
}