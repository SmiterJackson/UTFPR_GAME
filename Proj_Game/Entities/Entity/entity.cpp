#include "entity.h"

// OBS multiplas inserções em vector pode causar realocação de memória que perde a textura de um objeto
// List sendo encadeado não há o problema
Entity::Entity():
	Ente(), hitBox(), body(), texture()
{
	this->body.setTexture(this->texture);
};
Entity::Entity(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef, const sf::IntRect sheetCut):
	Ente(_type, elapsed_timeRef), hitBox(_hitBox), body(), texture()
{
	if(!textureRef.empty())
		this->texture.loadFromFile(textureRef);

	this->body.setTexture(this->texture);

	if(sheetCut.left != sheetCut.width && sheetCut.top != sheetCut.height)
	{
		this->body.setTextureRect(sheetCut);
		this->body.setOrigin(sheetCut.width / 2.f, sheetCut.height / 2.f);
	}
	else
		this->body.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().y / 2.f);

	if (this->hitBox.getSize().x > 0 && this->hitBox.getSize().y > 0)
		this->hitBox.setOrigin(this->hitBox.getSize().x / 2.f, this->hitBox.getSize().y / 2.f);

	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->hitBox.setPosition(0.f, 0.f);
	this->body.setPosition(0.f, 0.f);
};
Entity::~Entity()
{};

sf::Vector2f const Entity::GetPosition() const
{
	return this->hitBox.getPosition();
};
void Entity::MovePosition(const sf::Vector2f _newPosition)
{
	this->hitBox.move(_newPosition);
	this->body.move(_newPosition);
};

sf::FloatRect const Entity::GetHitBoxBounds() const
{
	sf::FloatRect bounds(
		this->hitBox.getPosition().x - (this->hitBox.getSize().x / 2.f),
		this->hitBox.getPosition().y - (this->hitBox.getSize().y / 2.f),
		this->hitBox.getPosition().x + (this->hitBox.getSize().x / 2.f),
		this->hitBox.getPosition().y + (this->hitBox.getSize().y / 2.f)
	);

	return bounds;
};
sf::Vector2f const Entity::GetHitBoxSize() const
{
	return this->hitBox.getSize();
};
void Entity::SetHitBoxSize(const sf::Vector2f _size)
{
	this->hitBox.setSize(_size);
};

sf::Vector2u const Entity::GetTextureSize()
{
	return this->texture.getSize();
};
void Entity::SetTexture(const std::string _texturePath, const sf::IntRect _rectCut)
{
	if (!_texturePath.empty())
	{
		this->texture.loadFromFile(_texturePath);
		if(_rectCut.left != _rectCut.width && _rectCut.top != _rectCut.height)
		{
			this->body.setTextureRect(_rectCut);
			this->body.setOrigin(_rectCut.width / 2.f, _rectCut.height / 2.f);
		}
		else
		{
			this->body.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().y / 2.f);
		}
		this->body.setPosition(this->hitBox.getPosition());
	}
};