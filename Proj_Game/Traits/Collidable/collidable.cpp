#include "collidable.h"

Trait::Collidable::Collidable(const bool inverseColisionType = false):
	inverseCollision(inverseColisionType)
{};
Trait::Collidable::~Collidable()
{};

void const Trait::Collidable::Collided(Collidable* _other)
{
	if (_other->GetCollisionType())
		this->OutsideOf_Collision(_other);
	else
		this->InsideOf_Collision(_other);
};
void Trait::Collidable::InsideOf_Collision(Collidable* _other)
{
	sf::Vector2f other(
		fabs(_other->GetBounds().width),
		fabs(_other->GetBounds().height)
	);
	sf::Vector2f size(
		fabs(this->GetBounds().width),
		fabs(this->GetBounds().height)
	);
	sf::Vector2f distance(
		_other->GetPosition().x - this->GetPosition().x,
		_other->GetPosition().y - this->GetPosition().y
	);
	sf::Vector2f intersection(
		fabs(distance.x) - (other.x + size.x),
		fabs(distance.y) - (other.y + size.y)
	);

	if (intersection.y >= intersection.x)
	{
		if (distance.y > 0.f)
			this->MovePosition(0.f, (intersection.y));
		else
			this->MovePosition(0.f, -(intersection.y));
	}
	else
	{
		if (distance.x > 0.f)
			this->MovePosition(intersection.x, 0.f);
		else
			this->MovePosition(-(intersection.x), 0.f);
	}
};
void Trait::Collidable::OutsideOf_Collision(Collidable* _other)
{
	sf::FloatRect entBounds(this->GetBounds());
	sf::FloatRect mapBounds(_other->GetBounds());

	if (entBounds.top < mapBounds.top || entBounds.height > mapBounds.height)
	{
		if (entBounds.top < mapBounds.top)
			this->MovePosition(sf::Vector2f(mapBounds.top - entBounds.top, 0.f));
		else
			this->MovePosition(sf::Vector2f(mapBounds.height - entBounds.height, 0.f));
	}
};