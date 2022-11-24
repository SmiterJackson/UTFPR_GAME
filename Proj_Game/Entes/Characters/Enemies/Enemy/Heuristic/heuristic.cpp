#include "heuristic.h"
#include "../Managers/GraphicManager/graphic_manager.h"

Heuristic::Heuristic(const double _cost, const double _distance,
					 const double _heuristic, const sf::Vector2i _neighbour):
	BaseHeuristc(_cost, _neighbour),
	distance(_distance), heuristic(_heuristic)
{};
Heuristic::~Heuristic()
{};
