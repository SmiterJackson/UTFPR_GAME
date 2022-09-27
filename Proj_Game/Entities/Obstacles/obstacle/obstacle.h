#pragma once

#include "../../Entity/entity.h"

namespace Obstacles 
{
	class Obstacle : public Entity
	{
	public:
		Obstacle();
		Obstacle(const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
		~Obstacle();

		virtual void Execute();
		virtual void Collided(Ente* _other);
	};
}