#pragma once

#include "../../Characters/Character/character.h"

namespace Projectiles
{
	class Projectile : public Entity
	{
	public:
		Projectile();
		Projectile(Characters::Character* _charOrigin, const sf::Vector2f _size, const sf::Vector2f _position, const float arrowSpeed = 1.0f,
	 			   const std::string path = "", const sf::IntRect sheetCut = sf::IntRect(),  const float size_coeff = 1.0f);
		~Projectile();

		virtual void SelfPrint(const float& pElapsedTime);

		virtual void Execute(const float& pElapsedTime) = 0;
		virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType) = 0;

	protected:
		Characters::Character* origin;

		float speedH;
	};
}