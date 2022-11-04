#include "obstacle.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Obstacles;
using namespace Manager;

Obstacle::Obstacle():
	Entity(Type::OBSTACLE, PrintPriority::obstacles, 
		   sf::Vector2f(0.f,0.f), sf::Vector2f(0.f, 0.f), true, 1.f),
	PrintableBody()
{};
Obstacle::Obstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
							  const sf::IntRect sheetCut, const float size_coeff, const bool isStatic, const bool repeated):
	Entity(Type::OBSTACLE, PrintPriority::obstacles, _size, _position, isStatic, size_coeff),
	PrintableBody(path, sheetCut, size_coeff)
{
	if(this->texture != nullptr)
		this->texture->setRepeated(repeated);
};
Obstacle::~Obstacle()
{};

void Obstacle::SelfPrint(const float& pElapsedTime)
{
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->origin);
#endif
};

void Obstacle::InCollision(Entity* _other, const sf::Vector2f& intersection)
{};
void Obstacle::OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
{};