#pragma once

#include "../../Player/player.h"

namespace Enemies
{
	typedef std::list<Characters::Player*> PlayerList;
	class Enemy : public Characters::Character
	{
	private:
		enum ASTAR_RETURN_TYPE
		{
			LEFT,
			RIGHT,
			UP
		};

	public:
		Enemy();
		Enemy(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
			const AnimationSheet _animations = AnimationSheet(), const unsigned int _lifeAmount = 0U, 
			const float invcDuration = 0.f, const float deathTime = 1.f, const float _agroRange = 1.f,
			const bool isStatic = true, const float proportion = 1.0f);
		virtual ~Enemy();

		virtual void SelfPrint();
		virtual void Attack() = 0;
		virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType) = 0;

	protected:
		virtual void Died() = 0;
		static unsigned int AStarAlgorithm(const sf::Vector2f pos);

	protected:
		static const PlayerList& players;

		bool agro;
		float agroRange;
	};
}