#include "obstacle.h"

Obstacles::Obstacle::Obstacle() :
	Entity(Type::OBSTACLE, sf::RectangleShape(), nullptr)
{};
Obstacles::Obstacle::Obstacle(const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef, const sf::IntRect sheetCut) :
	Entity(Type::OBSTACLE, _hitBox, elapsed_timeRef, textureRef, sheetCut)
{};
Obstacles::Obstacle::~Obstacle()
{};

void Obstacles::Obstacle::Execute()
{};
void Obstacles::Obstacle::SelfPrint(sf::RenderWindow& context_window)
{
	context_window.draw(this->body);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
	context_window.draw(this->hitBox);
#endif
};
void Obstacles::Obstacle::Collided(Entity* _other)
{};