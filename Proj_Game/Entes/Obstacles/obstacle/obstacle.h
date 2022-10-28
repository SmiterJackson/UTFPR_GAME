#pragma once

#include "../../Entity/entity.h"
#include "../../../Traits/Printable/printable.h"

namespace Obstacles
{
	class Obstacle : public Entity, public Trait::Printable
	{
	public:
		Obstacle();
		Obstacle(const sf::RectangleShape& _hitBox, const std::string textureRef = "",
				 const sf::IntRect sheetCut = sf::IntRect(), const float size_proportion = 1.0f,
				 const bool repeated = false);
		~Obstacle();

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
		virtual void Execute(const float& pElapsedTime);
	};
}