#include "node.h"
#include "../Managers/GraphicManager/graphic_manager.h"

Node::Node(const double _distance, const double _heuristic, const sf::Vector2i _previous):
	distance(_distance),
	heuristic(_heuristic),
	cost(this->distance + this->heuristic),
	previous(_previous)
{};
Node::~Node()
{};

double Node::CalcHeuristic(const sf::Vector2i& src, const sf::Vector2i& trg)
{
	double deltaX = double(abs(src.x - trg.x));
	double deltaY = double(abs(src.y - trg.y));

	if(deltaX > deltaY)
		return 14 * deltaY + 10 * (deltaX - deltaY);
	return 14 * deltaX + 10 * (deltaY - deltaX);
};