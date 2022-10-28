#pragma once

#include "../Ente/ente.h"
#include "../../Traits/Collidable/collidable.h"

/*
Classe de nível mais alto onde defini-se os requisitos da classe base de ser colidível,
bem como sendo uma instância defini seu tipo, e prepara novamente a função executar.
Em suma sendo um amalgama das classes herdadas.
*/
class Entity : public Ente, public Trait::Collidable
{
public:
	Entity();
	Entity(const unsigned int _type, const sf::RectangleShape& _hitBox = sf::RectangleShape(),
		   const float size_proportion = 1.0f, const bool inverseColisionType = false);
	virtual ~Entity();

	void SetHitBoxSize(const sf::Vector2f _size) { this->hitBox.setSize(_size); };
	const sf::Vector2f const GetHitBoxSize() const;

	const sf::FloatRect const GetBounds();

	const sf::Vector2f const GetPosition() const { return this->hitBox.getPosition(); };
	virtual void MovePosition(const sf::Vector2f _newPosition) { this->hitBox.move(_newPosition); };
	virtual void MovePosition(const float X_axis, const float Y_axis) { this->hitBox.move(X_axis, Y_axis); };

	virtual void SetProportion(const float proportion) { this->hitBox.setScale(proportion, proportion); };

	virtual void Execute(const float& pElapsedTime) = 0;

protected:
	sf::RectangleShape hitBox; // O corpo para interações
#ifdef _DEBUG
	sf::CircleShape origin;
#endif
};