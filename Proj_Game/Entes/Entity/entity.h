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
	Entity(const unsigned short int _type, const unsigned short int printPriority, const sf::Vector2f _size,
		   const sf::Vector2f _position, const std::string path, const sf::IntRect sheetCut,
		   const bool isStatic = true, const float proportion = 1.0f);
	virtual ~Entity();

	const bool IsStatic() const { return this->isStatic; };

	void SetTexture(const std::string path, const sf::IntRect sheetCut = sf::IntRect(0, 0, 0, 0));

	void SetProportion(const float proportion) 
	{ 
		this->hitBox.setScale(proportion, proportion); 
		this->body.setScale(proportion, proportion);
	};
	const float GetProportion() const { return this->hitBox.getScale().x; };

	virtual void SetHitBoxSize(const sf::Vector2f _size) { this->hitBox.setSize(_size); };
	const sf::Vector2f GetSize() const { return (this->hitBox.getSize() * this->hitBox.getScale().x); };
	const sf::FloatRect GetBounds() const
	{
		sf::Vector2f pos(this->hitBox.getPosition());
		sf::Vector2f size(this->GetSize() / 2.f);

		sf::FloatRect bounds(
			pos.x - size.x,
			pos.y - size.y,
			pos.x + size.x,
			pos.y + size.y
		);

		return bounds;
	};

	const sf::Vector2f GetPosition() const { return this->hitBox.getPosition(); };
	void MovePosition(const float X_axis, const float Y_axis) 
	{ 
		this->hitBox.move(X_axis, Y_axis);
		this->body.move(X_axis, Y_axis);
	};
	void SetPosition(const float X_axis, const float Y_axis)
	{
		this->hitBox.setPosition(X_axis, Y_axis);
		this->body.setPosition(X_axis, Y_axis);
	};

	virtual void Execute();
	virtual void SelfPrint() = 0;
	virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType) = 0;

	virtual bool operator!= (const Entity& other)
	{
		return this->id != other.id;
	};

protected:
	virtual void Move() = 0;

protected:
	static const float gravity;
	static const float maxGravityPull;
	const bool isStatic;

	sf::RectangleShape hitBox;
	sf::Texture* texture;
	sf::Sprite body;

#ifdef _DEBUG
	sf::CircleShape originCircle;
#endif
};