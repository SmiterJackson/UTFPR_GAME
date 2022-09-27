#pragma once

#include "../Ente/ente.h"

class Stage;

class Entity : public Ente
{
public:
	Entity();
	Entity(const unsigned int _type, float* pElapsedTime, const sf::RectangleShape& _hitBox,
			const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
	~Entity();

	virtual void Execute() = 0;
	virtual void Collided(Ente* _other) = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window);

	sf::Vector2f const GetPosition() const;
	void MovePosition(const sf::Vector2f _newPosition);
	void MovePosition(const float x, const float y);

	sf::FloatRect const GetHitBoxBounds() const;
	sf::Vector2f const GetHitBoxSize() const;
	void SetHitBoxSize(const sf::Vector2f _size);

	sf::Vector2u const GetTextureSize();
	void SetTexture(const std::string _texturePath, const sf::IntRect _rectCut = sf::IntRect(0, 0, 0, 0));

protected:
	virtual void ObstacleCollision(Entity* obstacle);
	virtual void StageCollision(Stage* stage);

protected:
	sf::RectangleShape hitBox; // O corpo para interações
	sf::Sprite body;		   // O corpo para representação gráfica
	sf::Texture texture;	   // Textura que irá preencher o "body" - sprite
};