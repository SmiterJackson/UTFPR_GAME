#pragma once

#include "stdafx.h"

namespace Trait
{
	class Collidable 
	{
	public:
		Collidable(const bool inverseColisionType = false);
		virtual ~Collidable();

		const bool& GetCollisionType() { return this->inverseCollision; };

		virtual const sf::FloatRect const GetBounds() = 0;

		virtual const sf::Vector2f const GetPosition() = 0;
		virtual void MovePosition(const sf::Vector2f _newPosition) = 0;
		virtual void MovePosition(const float X_axis, const float Y_axis) = 0;

		void const Collided(Collidable* _other);

	protected:
		virtual void InsideOf_Collision(Collidable* _other);
		virtual void OutsideOf_Collision(Collidable* _other);

	protected:
		const bool inverseCollision;
	};
}