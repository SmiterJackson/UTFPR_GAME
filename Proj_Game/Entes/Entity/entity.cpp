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
	isStatic(true), hitBox(), texture(nullptr), body()
{
	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->SetPosition(0.f, 0.f);
#ifdef _DEBUG
	this->hitBox.setOutlineThickness(1.5f);
	this->hitBox.setOutlineColor(sf::Color::Red);

	this->originCircle.setFillColor(sf::Color::Transparent);
	this->originCircle.setRadius(ORIGIN_SIZE);
	this->originCircle.setOrigin(ORIGIN_SIZE / 2.f, ORIGIN_SIZE / 2.f);
	this->originCircle.setOutlineThickness(2.5f);
	this->originCircle.setOutlineColor(sf::Color::Blue);
	this->originCircle.setPosition(this->hitBox.getPosition());
#endif
};
Entity::Entity(const unsigned short int _type, const unsigned short int printPriority, const sf::Vector2f _size,
			   const sf::Vector2f _position, const std::string path, const sf::IntRect sheetCut,
			   const bool isStatic, const float proportion) :
	Ente(_type, printPriority),
	isStatic(isStatic), hitBox(), texture(nullptr), body()
{
	if (!path.empty())
	{
		this->texture = GraphicManager::LoadTexture(path, sheetCut);

		if (this->texture != nullptr)
		{
			this->body.setTexture(*this->texture);
			this->texture->setRepeated(false);

			this->body.setOrigin(
				this->texture->getSize().x / 2.f,
				this->texture->getSize().y / 2.f
			);
		}
	}
	this->body.setScale(proportion, proportion);
	this->body.setPosition(_position);

	this->hitBox.setTexture(NULL);
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setSize(_size);
	this->hitBox.setPosition(_position);
	this->hitBox.setScale(proportion, proportion);
	this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);

#ifdef _DEBUG
	this->hitBox.setOutlineThickness(1.5f);
	this->hitBox.setOutlineColor(sf::Color::Red);

	this->originCircle.setFillColor(sf::Color::Transparent);
	this->originCircle.setRadius(ORIGIN_SIZE);
	this->originCircle.setOrigin(ORIGIN_SIZE / 2.f, ORIGIN_SIZE / 2.f);
	this->originCircle.setOutlineThickness(2.5f);
	this->originCircle.setOutlineColor(sf::Color::Blue);
	this->originCircle.setPosition(this->hitBox.getPosition());
#endif
};
Entity::~Entity()
{};

void Entity::SetTexture(const std::string path, const sf::IntRect sheetCut)
{
	if (!path.empty())
	{
		this->texture = GraphicManager::LoadTexture(path, sheetCut);

		if (this->texture != nullptr)
		{
			this->body.setTexture(*this->texture);
			this->texture->setRepeated(false);

			this->body.setOrigin(
				this->texture->getSize().x / 2.f,
				this->texture->getSize().y / 2.f
			);
		}
	}
};