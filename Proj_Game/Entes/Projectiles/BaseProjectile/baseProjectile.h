#pragma once

#include "../../Characters/Character/character.h"

namespace Projectiles
{
	class BaseProjectile : public Entity, public Trait::PrintableBody
	{
	public:
		BaseProjectile(Characters::Character* charOrigin, const sf::Vector2f _size, const sf::Vector2f _position,
					   const std::string path = "", const sf::IntRect sheetCut = sf::IntRect(), const float size_coeff = 1.0f);
		~BaseProjectile();

		const bool HaveCollided() { return this->collided; };

		void SetProportion(const float proportion) { this->hitBox.setScale(proportion, proportion); };

		void MovePosition(const sf::Vector2f _newPosition) { this->hitBox.move(_newPosition); };
		void MovePosition(const float X_axis, const float Y_axis) { this->hitBox.move(X_axis, Y_axis); };

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		virtual void Execute(const float& pElapsedTime);

	protected:
		virtual void InCollision(Entity* _other, const sf::Vector2f& intersection);
		virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);

	protected:
		Characters::Character* charOrigin;

		bool collided;
		float speed;
	};
}