#include "staticTile.h"
#include "../Entes/Characters/Character/character.h"
using namespace Obstacles;

#define SIZE 24

TypeToRoad NormalTile::roadTypeMap = {
	TypeToRoad::value_type(TileType::MOSS_LEFT_CORNER,	sf::IntRect(SIZE * 0, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::MOSS_MIDDLE,		sf::IntRect(SIZE * 1, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::MOSS_RIGHT_CORNER, sf::IntRect(SIZE * 3, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::ROCK_LEFT_CORNER,	sf::IntRect(SIZE * 5, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::ROCK_MIDDLE,		sf::IntRect(SIZE * 6, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::ROCK_RIGHT_CORNER, sf::IntRect(SIZE * 9, SIZE * 0, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::ROCK_LEFT_WALL,	sf::IntRect(SIZE * 0, SIZE * 1, SIZE, SIZE)),
	TypeToRoad::value_type(TileType::ROCK_RIGHT_WALL,	sf::IntRect(SIZE * 3, SIZE * 1, SIZE, SIZE))
};

NormalTile::NormalTile(const sf::Vector2u size, sf::Vector2f pos, const TileType type):
	Obstacle(
		sf::Vector2f(float(size.x * SIZE), float(size.y* SIZE)), pos, roadTypeMap.find(type)->second, 1.33f, true
	)
{};
NormalTile::~NormalTile()
{};

void NormalTile::Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType)
{
	if (colType != CollisionType::EntityColl || _other == nullptr)
		return;

	if (_other->GetType() == Type::PLAYER)
		static_cast<Characters::Character*>(_other)->SetSpeedCoeff(1.f);
};