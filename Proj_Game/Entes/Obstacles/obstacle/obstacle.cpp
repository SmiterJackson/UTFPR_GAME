#include "obstacle.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Obstacles;
using namespace Manager;

#define PATH "Proj_Game/Resources/tile_sets/oak_woods_v1.0/oak_woods_tileset.png"

Obstacle::Obstacle():
	Entity(
		Type::OBSTACLE, PrintPriority::obstacles, sf::Vector2f(0.f,0.f),
		sf::Vector2f(0.f, 0.f), std::string(""), sf::IntRect(0, 0, 0, 0)
	)
{};
Obstacle::Obstacle(const sf::Vector2f _size, const sf::Vector2f _position, const sf::IntRect sheetCut,
				   const float size_coeff, const bool isStatic):
	Entity(
		Type::OBSTACLE, PrintPriority::obstacles, _size, 
		_position, PATH, sheetCut, isStatic, size_coeff
	)
{
	if (this->texture != nullptr)
		this->texture->setRepeated(true);

	this->body.setTextureRect(sf::IntRect(0,0, int(_size.x), int(_size.y)));
	this->body.setOrigin(_size / 2.f);
	this->body.setPosition(this->hitBox.getPosition());
};
Obstacle::~Obstacle()
{};

void Obstacle::SelfPrint(const float& pElapsedTime)
{
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->originCircle);
#endif
};