#include "entity.h"
#include "../StageClass/stage.h"

// OBS multiplas inserções em vector pode causar realocação de memória que perde a textura de um objeto
// List sendo encadeado não há o problema
Entity::Entity():
	Ente(), hitBox(), body(), texture()
{
	this->body.setTexture(this->texture);
};
Entity::Entity(const unsigned int _type, float* pElapsedTime, const sf::RectangleShape& _hitBox,
			   const std::string textureRef, const sf::IntRect sheetCut):
	Ente(_type, pElapsedTime), hitBox(_hitBox), body(), texture()
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

#ifdef _DEBUG
	this->hitBox.setOutlineThickness(1.5f);
	this->hitBox.setOutlineColor(sf::Color::Red);
#endif
};
Entity::~Entity()
{};

void Entity::SelfPrint(sf::RenderWindow& context_window)
{
	context_window.draw(this->body);

#ifdef _DEBUG
	context_window.draw(this->hitBox);
#endif
};

sf::Vector2f const Entity::GetPosition() const
{
	return this->hitBox.getPosition();
};
void Entity::MovePosition(const sf::Vector2f _newPosition)
{
	this->hitBox.move(_newPosition);
	this->body.move(_newPosition);
};
void Entity::MovePosition(const float x, const float y)
{
	this->hitBox.move(x, y);
	this->body.move(x, y);
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
	this->hitBox.setOrigin(_size / 2.f);
	this->hitBox.setPosition(this->body.getPosition());
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

void Entity::ObstacleCollision(Entity* obstacle)
{
	sf::Vector2f intersection;
	sf::Vector2f obsSize(obstacle->GetHitBoxSize());
	sf::Vector2f size(this->GetHitBoxSize());
	sf::Vector2f distance(
		obstacle->GetPosition().x - this->GetPosition().x,
		obstacle->GetPosition().y - this->GetPosition().y
	);

	obsSize /= 2.0f;
	size /= 2.0f;

	intersection = sf::Vector2f(
		fabs(distance.x) - (obsSize.x + size.x),
		fabs(distance.y) - (obsSize.y + size.y)
	);

	if (intersection.y >= intersection.x)
	{
		if (distance.y > 0.f)
			this->MovePosition(0.f, (intersection.y));
		else
			this->MovePosition(0.f, -(intersection.y));
	}
	else
	{
		if (distance.x > 0.f)
			this->MovePosition(intersection.x, 0.f);
		else
			this->MovePosition(-(intersection.x), 0.f);
	}
};
void Entity::StageCollision(Stage* stage)
{
	sf::FloatRect entBounds(this->GetHitBoxBounds());
	sf::FloatRect mapBounds(stage->GetMapBounds());

	if (entBounds.top < mapBounds.top || entBounds.height > mapBounds.height)
	{
		if (entBounds.top < mapBounds.top)
			this->MovePosition(sf::Vector2f(mapBounds.top - entBounds.top, 0.f));
		else
			this->MovePosition(sf::Vector2f(mapBounds.height - entBounds.height, 0.f));
	}
};