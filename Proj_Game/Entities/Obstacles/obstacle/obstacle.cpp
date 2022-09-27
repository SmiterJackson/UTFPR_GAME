#include "obstacle.h"

Obstacles::Obstacle::Obstacle() :
	Entity(Type::OBSTACLE, nullptr, sf::RectangleShape())
{};
Obstacles::Obstacle::Obstacle(const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef, const sf::IntRect sheetCut) :
	Entity(Type::OBSTACLE, elapsed_timeRef, _hitBox, textureRef, sheetCut)
{};
Obstacles::Obstacle::~Obstacle()
{};

void Obstacles::Obstacle::Execute()
{};
void Obstacles::Obstacle::Collided(Ente* _other)
{};