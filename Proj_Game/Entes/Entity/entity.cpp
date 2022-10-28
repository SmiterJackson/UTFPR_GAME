#include "entity.h"

#ifdef _DEBUG
#define ORIGIN_SIZE 1.f
#endif

// OBS multiplas inserções em vector pode causar realocação de memória onde perde-se a textura do objeto
// List sendo encadeado não há o problema
Entity::Entity():
	Ente(UNDEFINED), Collidable(false), hitBox()
{
	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->hitBox.setPosition(0.f, 0.f);
};
Entity::Entity(const unsigned int _type, const sf::RectangleShape& _hitBox, 
			   const float size_proportion, const bool inverseColisionType) :
	Ente(_type), Collidable(inverseColisionType), hitBox(_hitBox)
{
	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setScale(size_proportion, size_proportion);
	this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
	this->hitBox.setPosition(0.f, 0.f);

#ifdef _DEBUG
	this->hitBox.setOutlineThickness(1.5f);
	this->hitBox.setOutlineColor(sf::Color::Red);

	this->origin.setFillColor(sf::Color::Transparent);
	this->origin.setRadius(ORIGIN_SIZE);
	this->origin.setOrigin(ORIGIN_SIZE / 2.f, ORIGIN_SIZE / 2.f);
	this->origin.setOutlineThickness(2.5f);
	this->origin.setOutlineColor(sf::Color::Blue);
	this->origin.setPosition(this->hitBox.getPosition());
#endif
};
Entity::~Entity()
{};

sf::FloatRect const Entity::GetBounds()
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
sf::Vector2f const Entity::GetHitBoxSize() const
{
	return (this->hitBox.getSize() * this->hitBox.getScale().x);
};