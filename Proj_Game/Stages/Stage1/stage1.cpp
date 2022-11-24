#include "stage1.h"
using namespace Characters;
using namespace Obstacles;
using namespace Enemies;
using namespace Stages;

#define OBSTACLE_SIZE 24

#define OBSTACLE_NUM 1.f
#define PLAYER_NUM 1

#define IMAGE_COEFFICIENT 1.f

#define SIZE sf::Vector2u(unsigned int(24U * 1U * IMAGE_COEFFICIENT), unsigned int(13U * IMAGE_COEFFICIENT))

const std::vector<std::string> Stage1::backgroundPaths = {
	"Proj_Game/Resources/parallax_background/Background_0.png",
	"Proj_Game/Resources/parallax_background/Background_1.png",
	"Proj_Game/Resources/parallax_background/Background_2.png"
};

Stage1::Stage1():
	Stage(SIZE, backgroundPaths, IMAGE_COEFFICIENT)
{
	this->Initalize();
	this->VerifyGridOcupation();
};
Stage1::~Stage1()
{};

void Stage1::Initalize()
{
	sf::Vector2f position(304.f, Stage::GetWorldSize().y - 80.f);
	float obsCoeff = 1.f;
	int i = 0, x_axis = 0, y_axis = 0;

	Player*		auxPlayer	= nullptr;
	Enemy*		auxEnemy	= nullptr;
	Obstacle*	auxObstacle = nullptr;

	for (i = 0; i < PLAYER_NUM; i++)
	{
		auxPlayer = new Player();
		auxPlayer->MovePosition(position.x, position.y);
		this->EntityCreated(auxPlayer);
	}

	for (i = 0; i < 1; i++)
	{
		auxEnemy = new EnemyMelee();
		auxEnemy->MovePosition(position.x + 64.f, position.y - 32.f);
		this->EntityCreated(auxEnemy);

		auxEnemy = new EnemyRanged();
		auxEnemy->MovePosition(position.x + 128.f, position.y - 32.f);
		this->EntityCreated(auxEnemy);
	}

	for (float f = 1.f; f < OBSTACLE_NUM + 1.f; f++)
	{
		auxObstacle = new NormalTile(
			sf::Vector2u(3, 1), sf::Vector2f(position.x + 128.f, position.y), TileType::MOSS_MIDDLE
		);
		this->EntityCreated(auxObstacle);

		auxObstacle = new NormalTile(
			sf::Vector2u(1, 1), sf::Vector2f(position.x + 64.f, position.y), TileType::MOSS_LEFT_CORNER
		);
		this->EntityCreated(auxObstacle);

		auxObstacle = new NormalTile(
			sf::Vector2u(1, 2), sf::Vector2f(position.x + 64.f, position.y + 48.f), TileType::ROCK_LEFT_WALL
		);
		this->EntityCreated(auxObstacle);
	}
};