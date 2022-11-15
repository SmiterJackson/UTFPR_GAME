#include "road.h"
#include "../Entes/Characters/Character/character.h"
using namespace Obstacles;

#define SIZE 24

TypeToRoad roadTypeMap = {
	TypeToRoad::value_type(RoadType::MOSS_LEFT_CORNER,	sf::IntRect(SIZE * 0, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(RoadType::MOSS_MIDDLE,		sf::IntRect(SIZE * 1, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(RoadType::MOSS_RIGHT_CORNER, sf::IntRect(SIZE * 3, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(RoadType::ROCK_LEFT_CORNER,	sf::IntRect(SIZE * 5, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(RoadType::ROCK_MIDDLE,		sf::IntRect(SIZE * 6, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(RoadType::ROCK_RIGHT_CORNER, sf::IntRect(SIZE * 9, SIZE * 0, SIZE, SIZE)),
};

Road::Road(sf::Vector2f size, sf::Vector2f pos, const RoadType type):
	Obstacle(
		size, pos, roadTypeMap.find(type)->second
	)
{};
Road::~Road()
{};

void Road::InCollision(Entity* _other, const sf::Vector2f& intersection)
{
	if (_other->GetType() == Type::PLAYER || _other->GetType() == Type::ENEMY)
		static_cast<Characters::Character*>(_other)->SetSpeedCoeff(0.7f);
};
void Road::OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
{};