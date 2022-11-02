#pragma once

#include "../Entes/Entity/entity.h"
#include "../Traits/PrintableBody/printableBody.h"

namespace Obstacles
{
	class Obstacle : public Entity, public Trait::PrintableBody
	{
	public:
		Obstacle();
		Obstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path = "",
				 const sf::IntRect sheetCut = sf::IntRect(), const float size_coeff = 1.0f,
				 const bool isStatic = true, const bool repeated = false);
		virtual ~Obstacle();

		void MovePosition(const sf::Vector2f _newPosition)
		{
			this->hitBox.move(_newPosition);
			this->SetTexturePosition(this->hitBox.getPosition());
		};
		void MovePosition(const float X_axis, const float Y_axis)
		{
			this->hitBox.move(X_axis, Y_axis);
			this->SetTexturePosition(this->hitBox.getPosition());
		};

		void SetProportion(const float proportion)
		{
			this->hitBox.setScale(proportion, proportion);
			this->SetTextureProportion(proportion);
		};

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
	
	protected:
		virtual void InCollision(const Entity* _other, const sf::Vector2f& intersection);
		virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);
	};
}