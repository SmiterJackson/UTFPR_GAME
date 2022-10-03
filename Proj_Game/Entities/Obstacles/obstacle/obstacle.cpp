#include "obstacle.h"

Obstacles::Obstacle::Obstacle() :
	Entity(Type::OBSTACLE, nullptr, sf::RectangleShape())
{};
Obstacles::Obstacle::Obstacle(float* elapsed_timeRef, const sf::RectangleShape& _hitBox, const std::string textureRef,
							  const sf::IntRect sheetCut, float _size_coeff) :
	Entity(Type::OBSTACLE, elapsed_timeRef, _hitBox, textureRef, sheetCut, _size_coeff)
{};
Obstacles::Obstacle::~Obstacle()
{};

void Obstacles::Obstacle::Execute()
{
#ifdef _DEBUG
	this->origin.setPosition(this->hitBox.getPosition());
#endif
};
void Obstacles::Obstacle::Collided(Ente* _other)
{};