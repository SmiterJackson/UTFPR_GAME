#pragma once

#include "../Entity/entity.h"

namespace Obstacles 
{
	class Obstacle : public Entity
	{
	public:
		Obstacle();
		Obstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
		~Obstacle();

		virtual void Execute() = 0;
		virtual void SelfPrint(sf::RenderWindow& context_window) = 0;
		virtual void Collided(const int type, const sf::Vector2f& movement) = 0;
	};
}