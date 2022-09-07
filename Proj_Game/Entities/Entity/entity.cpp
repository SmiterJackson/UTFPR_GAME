#include "entity.h"

Entity::Entity():
	Ente(Ente::UNDEFINED), hitBox(), body(), texture()
{
	this->body.setTexture(this->texture);
};
Entity::Entity(const unsigned int _type, const sf::RectangleShape& _hitBox, const sf::IntRect sheetCut, const std::string textureRef):
	Ente(_type), hitBox(_hitBox), body(), texture()
{
	if(!textureRef.empty())
		this->texture.loadFromFile(textureRef);

	this->body.setTexture(this->texture);

	if(sheetCut.height != 0 && sheetCut.width != 0)
		this->body.setTextureRect(sheetCut);

	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);
};
Entity::~Entity()
{};

const sf::Vector2f Entity::GetPosition()
{
	return this->hitBox.getPosition();
};
void Entity::MovePosition(const sf::Vector2f _newPosition)
{
	this->hitBox.move(_newPosition);
	this->body.move(_newPosition);
};