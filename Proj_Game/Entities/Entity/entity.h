#pragma once

#include "../Ente/ente.h"

class Entity : public Ente
{
public:
	Entity();
	Entity(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
	~Entity();

	virtual void Execute() = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window) = 0;
	virtual void Collided(const int type, const sf::Vector2f& movement) = 0;
	
	sf::Vector2f const GetPosition();
	void MovePosition(const sf::Vector2f _newPosition);

	sf::FloatRect const GetHitBoxBounds();
	sf::Vector2f const GetHitBoxSize();
	void SetHitBoxSize(const sf::Vector2f _size);

	sf::Vector2u const GetTextureSize();
	void SetTexture(const std::string _texturePath, const sf::IntRect _rectCut = sf::IntRect(0, 0, 0, 0));

protected:
	sf::RectangleShape hitBox; // O corpo para intera��es
	sf::Sprite body;		   // O corpo para representa��o gr�fica
	sf::Texture texture;	   // Textura que ir� preencher o "body" - sprite
};