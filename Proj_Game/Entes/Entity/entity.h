#pragma once

#include "../Ente/ente.h"

const enum CollisionType
{
	EntityColl = 0,
	CameraColl,
	MapColl
};

/*
Classe que junta os elementos da classe 'Ente' bem como 'Collidable', cujo objetivo
é disponibilizar uma entidade com pode interagir com outras.
*/
class Entity : public Ente
{
public:
	Entity();
	Entity(const unsigned short int _type, const unsigned short int printPriority, 
		   const sf::Vector2f _size, const sf::Vector2f _position, const bool isStatic = true,
		   const float size_coeff = 1.0f);
	virtual ~Entity();

	const bool GetIfStatic() const { return this->isStatic; };

	virtual void SetProportion(const float proportion) { this->hitBox.setScale(proportion, proportion); };

	void SetHitBoxSize(const sf::Vector2f _size) { this->hitBox.setSize(_size); };
	const sf::Vector2f GetHitBoxSize() const { return (this->hitBox.getSize() * this->hitBox.getScale().x); };
	const sf::FloatRect GetBounds() const
	{
		float scale(this->hitBox.getScale().x);

		sf::FloatRect bounds(
			this->hitBox.getPosition().x - ((this->hitBox.getSize().x * scale) / 2.f),
			this->hitBox.getPosition().y - ((this->hitBox.getSize().y * scale) / 2.f),
			this->hitBox.getPosition().x + ((this->hitBox.getSize().x * scale) / 2.f),
			this->hitBox.getPosition().y + ((this->hitBox.getSize().y * scale) / 2.f)
		);

		return bounds;
	};

	const sf::Vector2f GetPosition() const { return this->hitBox.getPosition(); };
	virtual void MovePosition(const sf::Vector2f _newPosition) { this->hitBox.move(_newPosition); };
	virtual void MovePosition(const float X_axis, const float Y_axis) { this->hitBox.move(X_axis, Y_axis); };

	virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
	virtual void Execute(const float& pElapsedTime);

	virtual void Collided(const Entity* _other, const sf::Vector2f& intersection, 
						  const const sf::FloatRect& otherBounds, const unsigned short int colType);

	virtual bool operator> (const Entity& other)
	{
		return this->type > other.type;
	};
	virtual bool operator< (const Entity& other)
	{
		return this->type < other.type;
	};
	virtual bool operator!= (const Entity& other)
	{
		return this->id != other.id;
	};

protected:
	virtual void InCollision(const Entity* _other, const sf::Vector2f& intersection,
							 const const sf::FloatRect& otherBounds);
	virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);

protected:
	const bool isStatic;
	sf::RectangleShape hitBox;

#ifdef _DEBUG
	sf::CircleShape origin;
#endif
};