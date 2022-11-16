#pragma once

#include "../Entes/Entity/entity.h"
#include "../Traits/PrintableBody/printableBody.h"

/*
Classe base para obstáculos.
*/
namespace Obstacles
{
	class Obstacle : public Entity
	{
	public:
		Obstacle();
		Obstacle(const sf::Vector2f _size, const sf::Vector2f _position, const sf::IntRect sheetCut = sf::IntRect(), 
				 const float size_coeff = 1.0f, const bool isStatic = true);
		virtual ~Obstacle();

		void SetHitBoxSize(const sf::Vector2f _size) 
		{ 
			this->hitBox.setSize(_size); 

			this->body.setTextureRect(sf::IntRect(0, 0, int(_size.x), int(_size.y)));
			this->body.setOrigin(_size / 2.f);
			this->body.setPosition(this->hitBox.getPosition());
		};

		virtual void SelfPrint(const float& pElapsedTime);

		virtual void Execute(const float& pElapsedTime) = 0;
		virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType) = 0;
	};
}