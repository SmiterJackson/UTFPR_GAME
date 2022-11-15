#pragma once

#include "../Ente/ente.h"

const enum CollisionType
{
	EntityColl = 0,
	CameraColl,
	MapColl
};

/*
Classe que herda características de 'Ente' onde diferencia-se no quesito de ser
um objeto que interage com outos dentro do jogo.
*/
class Entity : public Ente
{
public:
	Entity();
	Entity(const unsigned short int _type, const unsigned short int printPriority, 
		   const sf::Vector2f _size, const sf::Vector2f _position, const bool isStatic = true,
		   const float size_coeff = 1.0f);
	virtual ~Entity();

	const bool GetIsStatic() const { return this->isStatic; };

	virtual void SetProportion(const float proportion) { this->hitBox.setScale(proportion, proportion); };
	const float GetProportion() { return this->hitBox.getScale().x; };

	void SetHitBoxSize(const sf::Vector2f _size) { this->hitBox.setSize(_size); };
	const sf::Vector2f GetHitBoxSize() const { return (this->hitBox.getSize() * this->hitBox.getScale().x); };
	const sf::FloatRect GetBounds() const
	{
		sf::Vector2f pos(this->hitBox.getPosition());
		sf::Vector2f size(this->hitBox.getSize());
		float scale(this->hitBox.getScale().x);

		sf::FloatRect bounds(
			pos.x - ((size.x * scale) / 2.f),
			pos.y - ((size.y * scale) / 2.f),
			pos.x + ((size.x * scale) / 2.f),
			pos.y + ((size.y * scale) / 2.f)
		);

		return bounds;
	};

	const sf::Vector2f GetPosition() const { return this->hitBox.getPosition(); };
	virtual void MovePosition(const sf::Vector2f _newPosition) { this->hitBox.move(_newPosition); };
	virtual void MovePosition(const float X_axis, const float Y_axis) { this->hitBox.move(X_axis, Y_axis); };

	virtual void SelfPrint(const float& pElapsedTime) = 0;
	virtual void Execute(const float& pElapsedTime) = 0;

	virtual void Collided(Entity* _other, const sf::Vector2f& intersection, 
						  const sf::FloatRect& otherBounds, const unsigned short int colType);

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
	virtual void InCollision(Entity* _other, const sf::Vector2f& intersection) = 0;
	virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType) = 0;

protected:
	const bool isStatic;
	sf::RectangleShape hitBox;

#ifdef _DEBUG
	sf::CircleShape origin;
#endif
};