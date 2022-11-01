#include "obstacle.h"

Obstacles::Obstacle::Obstacle():
	Entity(Type::OBSTACLE, Manager::PrintPriority::obstacles, 
		   sf::Vector2f(0.f,0.f), sf::Vector2f(0.f, 0.f), true, 1.f),
	PrintableBody()
{};
Obstacles::Obstacle::Obstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
							  const sf::IntRect sheetCut, const float size_coeff, const bool isStatic, const bool repeated):
	Entity(Type::OBSTACLE, Manager::PrintPriority::obstacles, _size, _position, isStatic, size_coeff),
	PrintableBody(path, sheetCut, size_coeff)
{
	if(this->texture != nullptr)
		this->texture->setRepeated(repeated);
};
Obstacles::Obstacle::~Obstacle()
{};

void Obstacles::Obstacle::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	context_window.draw(this->body);
#ifdef _DEBUG
	context_window.draw(this->origin);
#endif
};