#include "baseHeuristic.h"

BaseHeuristc::BaseHeuristc(const double _cost, const sf::Vector2i _neighbour):
	cost(_cost), previous(_neighbour)
{};
BaseHeuristc::~BaseHeuristc()
{};

double BaseHeuristc::CalcHeuristic(const sf::Vector2i& src, const sf::Vector2i& trg)
{
	return abs(src.x - trg.x) + abs(src.y - trg.y);
};