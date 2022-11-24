#include "enemy.h"
#include "Heuristic/heuristic.h"
#include "../Entes/GUI/Interfaces/Stage/stage.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Enemies;

void tracePath(const std::vector<std::vector<Heuristic>> vals, const sf::Vector2i trg)
{
	printf("\n\nThe Path is ");
	int row = trg.x;
	int col = trg.y;

	std::stack<sf::Vector2i> Path;

	while (!(vals[row][col].previous.x == row
		&&	 vals[row][col].previous.y == col)) 
	{
		Path.push(sf::Vector2i(row, col));
		int temp_row = vals[row][col].previous.x;
		int temp_col = vals[row][col].previous.y;
		row = temp_row;
		col = temp_col;
	}

	Path.push(sf::Vector2i(row, col));
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
	std::vector<std::vector<bool>> closedList;
	std::vector<std::vector<Heuristic>> nodeValues;
	std::set<BaseHeuristc> openList;

	PlayerList::const_iterator it;
	sf::Vector2i src(GraphicManager::PositionToGrid(srcPos));
	sf::Vector2i target;

	constexpr double maxVal(std::numeric_limits<double>::max());
	double delta, least(maxVal);
	double f = 0.0, g = 0.0, h = 0.0;
	int i = 0, j = 0, x = 0, k = 0;
	bool found = false;

	closedList.resize(grid.size());
	nodeValues.resize(grid.size());
	for (i = 0; i < grid.size(); i++)
	{
		closedList[i].resize(grid[i].size(), false);
		nodeValues[i].resize(grid[i].size());
	}
	i = src.x;
	j = src.y;
	nodeValues[i][j].cost		= 0.0;
	nodeValues[i][j].distance	= 0.0;
	nodeValues[i][j].heuristic	= 0.0;
	nodeValues[i][j].previous	= src;
	openList.insert(BaseHeuristc(0.0, src));

	for (it = players.cbegin(); it != players.cend(); it++)
	{
		delta = sqrt(
			pow((*it)->GetPosition().x - srcPos.x, 2) +
			pow((*it)->GetPosition().y - srcPos.y, 2)
		);

		if (delta <= least)
		{
			least = delta;
			target = GraphicManager::PositionToGrid((*it)->GetPosition());
		}
	};

	if(src == target)
	{
		std::cout << "Ja esta no alvo." << std::endl;
		return 1;
	}

	while(!openList.empty())
	{
		BaseHeuristc current = *openList.begin();
		openList.erase(openList.begin());

		i = current.previous.x;
		j = current.previous.y;
		closedList[i][j] = true;

		for (x = i - 1; x <= i + 1; x++)
		{
			if (x < 0)
				x++;
			if (x >= nodeValues.size())
				break;

			for (k = j - 1; k <= j + 1; k++)
			{
				if (k < 0)
					k++;
				if ((x == i && k == j))
					k++;
				if (k >= nodeValues[x].size())
					break;

				if(sf::Vector2i(x, k) == target)
				{
					nodeValues[x][k].previous.x = i;
					nodeValues[x][k].previous.y = j;
					tracePath(nodeValues, target);
					found = true;
					goto endloop;
				}
				else if(closedList[x][k] == false && grid[x][k] == true)
				{
					g = nodeValues[i][j].distance + 1.0;
					h = Heuristic::CalcHeuristic(sf::Vector2i(x, k), target);
					f = g + h;

					if(nodeValues[x][k].cost == maxVal ||
					   nodeValues[x][k].cost < f)
					{
						std::cout << "Fui para -> (" << x << ", \t" << k << ");" << std::endl;
						openList.insert(BaseHeuristc(f, sf::Vector2i(x, k)));
						nodeValues[x][k].cost		= f;
						nodeValues[x][k].distance	= g;
						nodeValues[x][k].heuristic	= h;
						nodeValues[x][k].previous.x = i;
						nodeValues[x][k].previous.y = j;
					}
				}
			}
		}
	}
	endloop:

	if (!found)
		std::cout << "\nNao foi possivel achar o jogador." << std::endl;

	return 1;
};