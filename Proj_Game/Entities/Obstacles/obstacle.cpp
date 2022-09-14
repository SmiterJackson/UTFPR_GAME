#include "obstacle.h"

Obstacles::Obstacle::Obstacle() :
	Entity()
{};
Obstacles::Obstacle::Obstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef, const sf::IntRect sheetCut) :
	Entity(_type, _hitBox, elapsed_timeRef, textureRef, sheetCut)
{};
Obstacles::Obstacle::~Obstacle()
{};