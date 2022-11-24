#pragma once

#include "stdafx.h"

class BaseHeuristc
{
public:
	BaseHeuristc(const double _heuristic = std::numeric_limits<double>::max(), const sf::Vector2i _neighbour = sf::Vector2i(-1, -1));
	~BaseHeuristc();

	static double CalcHeuristic(const sf::Vector2i& src, const sf::Vector2i& trg);

	virtual bool operator<(BaseHeuristc& other)
	{
		return this->cost < other.cost;
	};

	double cost;
	sf::Vector2i previous;
};

inline bool operator<(const BaseHeuristc& first, const BaseHeuristc& second)
{
	return first.cost < second.cost;
};