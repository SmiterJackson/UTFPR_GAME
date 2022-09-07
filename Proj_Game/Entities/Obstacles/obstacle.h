#pragma once

#include "../Entity/entity.h"

namespace Obstacles 
{
	class Obstacle : public Entity
	{
	public:
		Obstacle();
		Obstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, const sf::IntRect sheetCut = sf::IntRect(), const std::string textureRef = "");
		~Obstacle();


		const sf::Vector2f GetPosition();
		void MovePosition(const sf::Vector2f _newPosition);

		void Execute(const float elapsedTime);
		void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime);
		void Collided(const Entity* _other);

	private:

	};
}