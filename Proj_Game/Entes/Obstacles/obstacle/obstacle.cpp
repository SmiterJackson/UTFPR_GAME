#include "obstacle.h"

Obstacles::Obstacle::Obstacle():
	Entity(Type::OBSTACLE, sf::RectangleShape(), 1.f, false), 
	Printable(PrintPriority::OBSTACLE)
{};
Obstacles::Obstacle::Obstacle(const sf::RectangleShape& _hitBox, const std::string textureRef,
							  const sf::IntRect sheetCut, const float size_proportion,
							  const bool TxtRepeated) :
	Entity(Type::OBSTACLE, _hitBox, size_proportion, false),
	Printable(PrintPriority::OBSTACLE, textureRef, sheetCut, size_proportion)
{
	this->texture.setRepeated(TxtRepeated);
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
void Obstacles::Obstacle::Execute(const float& pElapsedTime)
{
#ifdef _DEBUG
	this->origin.setPosition(this->hitBox.getPosition());
#endif
};