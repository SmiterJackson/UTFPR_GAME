#include "stage.h"
#include "../game/game.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Characters;
using namespace Manager;
using namespace Trait;
using namespace GUI;

#define RECT_SIZE 50.f

#define OBSTACLE_SIZE 24

#define OBSTACLE_NUM 1.f
#define PLAYER_NUM 1

Stage::Stage():
	Interface(GameStateType::IN_GAME),
	Observer(this->id),
	worldBounds(),
	colision_manager(nullptr),
	background(),
	entities()
{
	this->Initalize(1.f);
};
Stage::Stage(const sf::FloatRect bounds, const std::string& stagePath,
			 const std::vector<std::string>& BackgroundPaths, const float size_coefficient):
	Interface(GameStateType::IN_GAME),
	Observer(this->id),
	worldBounds(bounds.left, bounds.top, bounds.width, bounds.height /* + 200.f*/),
	colision_manager(nullptr),
	background(BackgroundPaths, size_coefficient),
	entities()
{
	colision_manager = ColisionManager::GetInstance(*this);
	GraphicManager::SetCameraLimits(bounds);

	this->Initalize(size_coefficient);

	GraphicManager::UpdateCamera();
	this->background.ResetBackground();
};
Stage::~Stage()
{
	Lista<Entity*>::Iterador it;

	for(it = this->entities.begin(); it != this->entities.end(); it++)
	{
		delete (*it);
		this->entities.PopAt(it);
	}
};

void Stage::Initalize(const float size_coefficient)
{
	Lista<Entity*> colidiveis;

	sf::Vector2f position(0.f, (192 * size_coefficient) - RECT_SIZE - 36.f);
	float obsCoeff = 1.f;
	int i = 0, x_axis = 0, y_axis = 0;
	
	std::list<Player*> players;
	for (i = 0; i < PLAYER_NUM; i++)
	{
		players.push_back(new Player());
		players.back()->MovePosition(position + sf::Vector2f(-48.f * i, 0.f));
		
		this->entities.PushBack(static_cast<Entity*>(players.back()));
		colidiveis.PushBack(static_cast<Entity*>(players.back()));
	}

	std::list<Obstacles::Obstacle*> obstacles;
	for (float f = 1.f; f < OBSTACLE_NUM + 1.f; f++)
	{
		sf::Vector2f obsSize(OBSTACLE_SIZE * 5, OBSTACLE_SIZE * 1);

		obstacles.push_back(new Obstacles::MossRoad(
			obsSize, sf::Vector2f(0.f,0.f)
		));
		obstacles.back()->MovePosition(sf::Vector2f(position.x + (obsSize.x * f * obsCoeff), position.y + 32 * 1.2f));
		
		this->entities.PushBack(static_cast<Entity*>(obstacles.back()));
		colidiveis.PushBack(static_cast<Entity*>(obstacles.back()));
	}
	this->colision_manager->AddRange(&colidiveis);
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

void Stage::SelfPrint(const float& pElapsedTime)
{
	Lista<Entity*>::Iterador it;

	this->background.SelfPrint(pElapsedTime);
	for(it = this->entities.begin(); it != this->entities.end(); it++)
		(*it)->SelfPrint(pElapsedTime);
};
void Stage::Execute(const float& pElapsedTime)
{
	unsigned int i = 0;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		this->entities[i].GetInfo()->Execute(pElapsedTime);
	}
	Manager::GraphicManager::UpdateCamera();

	this->colision_manager->UpdateColisions(pElapsedTime);
	this->background.Execute(pElapsedTime);
};

void Stage::AddEntity(Entity* entity)
{
	if (entity == nullptr)
		return;

	this->entities.PushBack(entity);
	this->colision_manager->Add(static_cast<Entity*>(entity));
};
void Stage::AddRange(std::list<Entity*>* _entities)
{
	std::list<Entity*>::iterator it;

	if (_entities == nullptr)
		return;

	for(it = _entities->begin(); it != _entities->end(); it++)
	{
		this->entities.PushBack(*it);
		this->colision_manager->Add(static_cast<Entity*>(*it));
	}
};
void Stage::RemoveEntity(const unsigned long long int entityId)
{
	Lista<Entity*>::Iterador it;

	for(it = this->entities.begin(); it != this->entities.end(); it++)
	{
		if ((*it)->GetId() == entityId)
		{
			delete (*it);
			this->entities.PopAt(it);
			break;
		}
	}

	this->colision_manager->Remove(entityId);
};
void Stage::RemoveRange(const std::vector<unsigned long long int> entityId)
{
	std::vector<unsigned long long int>::const_iterator cIt;
	Lista<Entity*>::Iterador it;

	for (cIt = entityId.cbegin(); cIt != entityId.cend(); cIt++)
	{
		for (it = this->entities.begin(); it != this->entities.end(); ++it)
		{

			if ((*it)->GetId() == (*cIt))
			{
				delete (*it); 
				this->entities.PopAt(it);
			}

			this->colision_manager->Remove(*cIt);
		}
	}
};

void Stage::AddPlayer()
{
	Characters::Player* player = Characters::Player::GetPlayerList().front();
	Characters::Player* newPlayer = nullptr;
	
	newPlayer = new Characters::Player();
	if(newPlayer == nullptr)
	{
		std::cerr << "Nao foi possivel criar um novo Jogador." << std::endl;
		return;
	}
	newPlayer->MovePosition(player->GetPosition());

	this->entities.PushBack(static_cast<Entity*>(newPlayer));
	this->colision_manager->Add(static_cast<Entity*>(newPlayer));
};
void Stage::RemovePlayer()
{
	Characters::Player* player = Characters::Player::GetPlayerList().back();

	this->colision_manager->Remove(player->GetId());
	this->RemoveEntity(player->GetId());
};