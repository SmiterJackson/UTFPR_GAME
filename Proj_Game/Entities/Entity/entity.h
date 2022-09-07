#pragma once

#include "../Ente/ente.h"

class Entity : public Ente
{
public:
	Entity();
	Entity(const unsigned int _type, const sf::RectangleShape& _hitBox, const sf::IntRect sheetCut = sf::IntRect(), const std::string textureRef = "");
	~Entity();

	const sf::Vector2f GetPosition();
	void MovePosition(const sf::Vector2f _newPosition);

	virtual void Execute(const float elapsedTime) = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime) = 0;
	virtual void Collided(const int type, const sf::Vector2f& movement) = 0;

protected:
	sf::RectangleShape hitBox; // O corpo para interações
	sf::Sprite body;		   // O corpo para representação gráfica
	sf::Texture texture;	   // Textura que irá preencher o "body" - sprite
};