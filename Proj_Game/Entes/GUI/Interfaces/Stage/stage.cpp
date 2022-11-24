#include "stage.h"
#include "../game/game.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Characters;
using namespace Manager;
using namespace Trait;
using namespace GUI;

#define THREADS_TO_PRINT_GRID 4

sf::RectangleShape Stage::world = sf::RectangleShape();
std::vector<std::vector<bool>> Stage::worldGrid = std::vector<std::vector<bool>>();

#ifdef _DEBUG
Stage::GridBlocks Stage::worldGridBlocks = GridBlocks();
#endif

Stage::Stage():
	Interface(GameStateType::IN_GAME),
	Observer(this->id),
	colision_manager(nullptr),
	background(),
	entities()
{};
Stage::Stage(const sf::Vector2u worldSize_grid, const std::vector<std::string>& BackgroundPaths, const float proportion):
	Interface(GameStateType::IN_GAME),
	Observer(this->id),
	colision_manager(nullptr),
	background(BackgroundPaths, proportion),
	entities()
{
	sf::Vector2f size(static_cast<sf::Vector2f>(worldSize_grid) * GraphicManager::GetGridSize());
	unsigned int i = 0, j = 0;

	worldGrid.resize(worldSize_grid.x);
	for (i = 0; i < worldSize_grid.x; i++)
		worldGrid[i].resize(worldSize_grid.y, true);

#ifdef _DEBUG
	sf::RectangleShape gridBlock;
	sf::Text txt;
	txt.setFont(*GraphicManager::GetFont());
	txt.setCharacterSize(10);
	gridBlock.setSize(sf::Vector2f(GraphicManager::GetGridSize(), GraphicManager::GetGridSize()));
	gridBlock.setFillColor(sf::Color(0U, 0U, 255U, 100U));
	gridBlock.setOutlineColor(sf::Color::Magenta);
	gridBlock.setOutlineThickness(0.5f);

	worldGridBlocks.resize(worldSize_grid.x);
	for (i = 0; i < worldSize_grid.x; i++)
		worldGridBlocks[i].resize(worldSize_grid.y, std::make_pair(gridBlock, txt));

	for (i = 0; i < worldSize_grid.x; i++)
		for (j = 0; j < worldSize_grid.y; j++)
		{
			std::stringstream ss;
			ss << "(" << i << ", " << j << ")";
			worldGridBlocks[i][j].first.setPosition(sf::Vector2f(
					GraphicManager::GetGridSize() * i,
					GraphicManager::GetGridSize() * j
				)
			);
			worldGridBlocks[i][j].second.setString(ss.str());
			worldGridBlocks[i][j].second.setPosition(sf::Vector2f(
					GraphicManager::GetGridSize() * i + 6.f,
					GraphicManager::GetGridSize() * j + 7.f
				)
			);
		}
#endif

	world.setSize(size);
	world.setOrigin(size / 2.f);
	world.setPosition(size / 2.f);

	colision_manager = ColisionManager::GetInstance();
	GraphicManager::SetCameraLimits(sf::FloatRect(0.f, 0.f, size.x, size.y));

	GraphicManager::UpdateCamera();
	this->background.ResetBackground();
};
Stage::~Stage()
{};

void Stage::VerifyGridOcupation()
{
	float grid(GraphicManager::GetGridSize());
	unsigned int i = 0;
	int j = 0, x = 0;
	sf::FloatRect sizeInGrid;
	sf::IntRect LimToGrid;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		if(this->entities[i]->GetType() == Type::OBSTACLE)
		{
			Obstacles::Obstacle* ob = static_cast<Obstacles::Obstacle*>(this->entities[i]);
			sizeInGrid = sf::FloatRect(
				this->entities[i]->GetBounds().left		/ grid,
				this->entities[i]->GetBounds().width	/ grid,
				this->entities[i]->GetBounds().top		/ grid,
				this->entities[i]->GetBounds().height	/ grid
			);
			LimToGrid = sf::IntRect(
				int(roundf(sizeInGrid.left)),
				int(roundf(sizeInGrid.width)),
				int(roundf(sizeInGrid.top)),
				int(roundf(sizeInGrid.height))
			);

			for (j = LimToGrid.left; j < LimToGrid.width; j++)
			{
				for (x = LimToGrid.top; x < LimToGrid.height; x++)
				{
					worldGrid[j][x].flip();
				#ifdef  _DEBUG
					worldGridBlocks[j][x].first.setFillColor(worldGrid[j][x] == true ? sf::Color(0U, 0U, 255U, 100U) : sf::Color(255U, 0U, 0U, 100U));
				#endif
				}
			}
		}
	}
};

void Stage::UpdateObsever(const sf::Event& _event)
{
	if(Game::GetGameState() == GameStateType::IN_GAME)
	{
		if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
		{
			Game::SetGameState(GameStateType::PAUSE_MENU);
			EventManager::InputSubject::InvertStopWarning();
		}
	}
};
void Stage::SelfPrint()
{
	unsigned int i = 0, j = 0;

	this->background.SelfPrint();
	for (i = 0; i < this->entities.GetSize(); i++)
	{
		this->entities[i]->SelfPrint();
	}

#ifdef _DEBUG
	sf::IntRect bounds(GraphicManager::CameraGridIndexs());
	sf::Vector2u extra((bounds.width - bounds.left) % 2 == 1 ? 1 : 0, (bounds.height - bounds.top) % 2 == 1 ? 1 : 0);
	sf::Vector2u half_diff((bounds.width - bounds.left) / 2u, (bounds.height - bounds.top) / 2u);
	sf::IntRect aux;

	for (i = bounds.left; i < bounds.width; i++)
		for (j = bounds.top; j < bounds.height; j++)
		{
			GraphicManager::Draw(worldGridBlocks[i][j].first);
			GraphicManager::Draw(worldGridBlocks[i][j].second);
		}
#endif
};
void Stage::Execute()
{
	unsigned int i = 0;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		this->entities[i]->Execute();
	}
	this->colision_manager->UpdateColisions(elapsedTime);

	Manager::GraphicManager::UpdateCamera();
	this->background.Execute();
};

void Stage::AddPlayer()
{
	Player* player = Characters::Player::GetPlayerList().front();
	Player* newPlayer = nullptr;
	sf::Vector2f pos(player->GetPosition());
	
	newPlayer = new Player();
	if(newPlayer == nullptr)
	{
		std::cerr << "Nao foi possivel criar um novo Jogador." << std::endl;
		return;
	}
	newPlayer->MovePosition(pos.x, pos.y);

	this->entities.AddEntity(static_cast<Entity*>(newPlayer));
	this->colision_manager->Add(static_cast<Entity*>(newPlayer));
};
void Stage::RemovePlayer()
{
	Characters::Player* player = Characters::Player::GetPlayerList().back();

	this->colision_manager->Remove(player->GetId());
	this->entities.RemoveEntity(player->GetId());
};

void Stage::EntityCreated(Entity* pEntity)
{
	if (pEntity == nullptr)
		return;

	this->entities.AddEntity(pEntity);
	this->colision_manager->Add(pEntity);
};