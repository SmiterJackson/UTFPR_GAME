#pragma once

#include "../obstacle/obstacle.h"

namespace Obstacles
{
	enum TileType
	{
		MOSS_LEFT_CORNER,
		MOSS_MIDDLE,
		MOSS_RIGHT_CORNER,
		ROCK_LEFT_CORNER,
		ROCK_MIDDLE,
		ROCK_RIGHT_CORNER,
		ROCK_LEFT_WALL,
		ROCK_RIGHT_WALL
	};
	typedef std::unordered_map<TileType, sf::IntRect> TypeToRoad;

	class NormalTile : public Obstacle
	{
	public:
		NormalTile(const sf::Vector2u size, sf::Vector2f pos, const TileType type);
		~NormalTile();

	protected:
		static TypeToRoad roadTypeMap;

		void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType);
	};
}