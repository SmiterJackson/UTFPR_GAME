#pragma once

#include "../obstacle/obstacle.h"

namespace Obstacles
{
	enum RoadType
	{
		MOSS_LEFT_CORNER,
		MOSS_MIDDLE,
		MOSS_RIGHT_CORNER,
		ROCK_LEFT_CORNER,
		ROCK_MIDDLE,
		ROCK_RIGHT_CORNER,
	};
	typedef std::unordered_map<RoadType, sf::IntRect> TypeToRoad;

	class Road : public Obstacle
	{
	public:
		Road(sf::Vector2f size, sf::Vector2f pos, const RoadType type);
		~Road();

	protected:
		static TypeToRoad roadTypeMap;

		void InCollision(Entity* _other, const sf::Vector2f& intersection);
		void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);
	};
}