#include "enemy.h"
#include "../Entes/GUI/Interfaces/Stage/stage.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Enemies;

void tracePath(NodeList& closed, const Node& trg)
{
	printf("\n\nThe Path is ");
	NodeList::iterator previous = closed.find(trg.previous);

	std::stack<sf::Vector2i> Path;

	Path.push(previous->first);
	while (previous->first != previous->second.previous)
	{
		Path.push(previous->second.previous);
		previous = closed.find(previous->second.previous);
	}

	while (!Path.empty()) 
	{
		sf::Vector2i p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.x, p.y);
	}

	return;
};

const PlayerList& Enemy::players(Characters::Player::GetPlayerList());

Enemy::Enemy():
	Character(
		
	), 
	agro(false), 
	agroRange(100.f)
{};
Enemy::Enemy(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
			 const AnimationSheet _animations, const unsigned int _lifeAmount,
			 const float invcDuration, const float deathTime, const float _agroRange,
			 const bool isStatic, const float proportion) :
	Character(
		Type::ENEMY, _size, _position, path,
		_animations, _lifeAmount, invcDuration,
		deathTime, isStatic, proportion
	),
	agro(false),
	agroRange(_agroRange)
{};
Enemy::~Enemy()
{};

void Enemy::SelfPrint()
{
	this->UpdateAnimation(elapsedTime);
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->originCircle);
#endif
};

unsigned int Enemy::AStarAlgorithm(const sf::Vector2f srcPos)
{
	std::vector<std::vector<bool>> grid = GUI::Stage::GetGridStatus();
	NodeList::iterator  it;
	NodeList closedList;
	NodeList openList;
	Node currentNode;
	Node neighbour;

	PlayerList::const_iterator cit;
	sf::Vector2i src(GraphicManager::PositionToGrid(srcPos));
	sf::Vector2i currentValue;
	sf::Vector2i neighbourPos;
	sf::Vector2i target;

	constexpr double maxVal(std::numeric_limits<double>::max());
	double delta = 0.0, totalcost = 0.0, least(maxVal);
	int x = 0, y = 0;
	bool found = false;

	for (cit = players.cbegin(); cit != players.cend(); cit++)
	{
		delta = sqrt(
			pow((*cit)->GetPosition().x - srcPos.x, 2) +
			pow((*cit)->GetPosition().y - srcPos.y, 2)
		);

		if (delta <= least)
		{
			least = delta;
			target = GraphicManager::PositionToGrid((*cit)->GetPosition());
		}
	};
	openList.emplace(src, Node(0.0, 0.0, src));

	if(src == target)
	{
		std::cout << "Ja esta no alvo." << std::endl;
		return 1;
	}

	while(!openList.empty())
	{
		currentValue = openList.begin()->first;
		currentNode = openList.begin()->second;
		least = maxVal;

		for (it = openList.begin(); it != openList.end(); it++)
		{
			if (it->second.cost < currentNode.cost || it->second <= currentNode)
			{
				currentValue = it->first;
				currentNode = it->second;
			}
		}

		if (currentValue == target)
		{
			tracePath(closedList, currentNode);
			found = true;
			break;
		}

		if (currentValue.x < 0 || currentValue.y < 0)
		{
			bool val = true;
		}

		openList.erase(currentValue);
		closedList.insert(NodeList::value_type(currentValue, currentNode));

		for (x = currentValue.x - 1; x <= currentValue.x + 1; x++)
		{
			if (x < 0)
				x++;
			if (x >= grid.size())
				break;

			for (y = currentValue.y - 1; y <= currentValue.y + 1; y++)
			{
				neighbourPos = sf::Vector2i(x, y);
				totalcost = currentNode.distance + Node::CalcHeuristic(currentValue, target);

				if (y < 0)
					y++;
				if ((x == currentValue.x && y == currentValue.y))
					y++;
				if (y >= grid[x].size())
					break;

				it = closedList.find(neighbourPos);
				if (grid[currentValue.x][currentValue.y] == false || it != closedList.end())
					continue;
				
				it = openList.find(neighbourPos);
				if (totalcost < neighbour.distance || it == openList.end())
				{
					neighbour.distance	= totalcost;
					neighbour.heuristic = Node::CalcHeuristic(neighbourPos, target);
					neighbour.previous	= currentValue;
					if (it == openList.end())
					{
						std::cout << "Fui para -> (" << x << ", \t" << y << ");" << std::endl;
						openList.insert(NodeList::value_type(neighbourPos, neighbour));
					}
				}
			}
		}
	}

	if (!found)
		std::cout << "\nNao foi possivel achar o jogador." << std::endl;

	return 1;
};