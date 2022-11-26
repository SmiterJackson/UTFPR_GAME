#pragma once

#include "stdafx.h"


class Node
{
public:
	Node(const double _distance = 0.0, const double _heuristic = 0.0, const sf::Vector2i _previous = sf::Vector2i(0, 0));
	~Node();

	static double CalcHeuristic(const sf::Vector2i& src, const sf::Vector2i& trg);

	bool operator<=(const Node& second)
	{
		return (this->cost == second.cost && this->heuristic < second.heuristic);
	}

	double distance;
	double heuristic;
	double cost;
	sf::Vector2i previous;
};

inline bool operator<=(const Node& first, const Node& second)
{
	return (first.cost == second.cost && first.heuristic < second.heuristic);
}

namespace std {

	template <>
	struct hash<sf::Vector2i>
	{
		std::size_t operator()(const sf::Vector2i& key) const
		{
			return (hash<int>()(key.x) ^ (hash<int>()(key.y) << 1)) >> 1;
		};
	};

}