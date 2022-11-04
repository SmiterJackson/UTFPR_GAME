#include "entity.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;

#ifdef _DEBUG
#define ORIGIN_SIZE 1.f
#endif

// OBS multiplas inserções em vector pode causar realocação de memória onde perde-se a textura do objeto
// List sendo encadeado não há o problema
Entity::Entity():
	Ente(Type::UNDEFINED, PrintPriority::undefined),
	isStatic(true), hitBox()
{
	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->hitBox.setPosition(0.f, 0.f);
};
Entity::Entity(const unsigned short int _type, const unsigned short int printPriority,
			   const sf::Vector2f _size, const sf::Vector2f _position, const bool isStatic,
			   const float size_coeff) :
	Ente(_type, printPriority),
	isStatic(isStatic), hitBox()
{
	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setSize(_size);
	this->hitBox.setPosition(_position);
	this->hitBox.setScale(size_coeff, size_coeff);
	this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);

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

void Entity::SelfPrint(const float& pElapsedTime)
{
#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->origin);
#endif
};
void Entity::Execute(const float& pElapsedTime)
{

#ifdef _DEBUG
	this->origin.setPosition(this->hitBox.getPosition());
#endif
};

void Entity::Collided(Entity* _other, const sf::Vector2f& intersection,
					  const sf::FloatRect& otherBounds, const unsigned short int colType)
{
	if (colType == CollisionType::CameraColl || colType == CollisionType::MapColl)
		this->OfCollision(otherBounds, colType);
	else
		this->InCollision(_other, intersection);
};