#pragma once

#include "../../Entity/entity.h"

namespace Obstacles 
{
	class Obstacle : public Entity
	{
	public:
		Obstacle();
		Obstacle(float* elapsed_timeRef, const sf::RectangleShape& _hitBox, const std::string textureRef = "",
				 const sf::IntRect sheetCut = sf::IntRect(), float _size_coeff = 1.0f);
		~Obstacle();

		virtual void Execute();
		virtual void Collided(Ente* _other);
	};
}