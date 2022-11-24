#pragma once

#include "../BaseHeuristic/baseHeuristic.h"

class Heuristic : public BaseHeuristc
{
public:
	Heuristic(const double _cost = std::numeric_limits<double>::max(), const double _distance = std::numeric_limits<double>::max(),
			  const double _heuristic = std::numeric_limits<double>::max(), const sf::Vector2i _neighbour = sf::Vector2i(-1, -1));
	~Heuristic();

	double distance;
	double heuristic;
};

