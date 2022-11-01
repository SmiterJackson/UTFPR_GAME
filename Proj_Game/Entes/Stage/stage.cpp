#include "stage.h"
using namespace Manager;
using namespace Trait;

#define RECT_SIZE 50.f

#define OBSTACLE_TEXTURE_REF "Proj_Game/Resources/tile_sets/Texture/TX_Tileset_Ground.png"
#define OBSTACLE_SIZE 32

#define PLAYER_NUM 1

Stage::Stage():
	Interface(GameStateType::IN_GAME),
	colision_manager(*this), background(),
	entities(), pGameState(nullptr)
{
	this->Initalize(1.f);
};
Stage::Stage(unsigned short int* pGameState, const sf::RectangleShape& _hitBox, const std::string& stagePath,
			 const std::vector<std::string>& BackgroundPaths, const float size_coefficient):
	Interface(GameStateType::IN_GAME),
	colision_manager(*this),
	background(),
	entities(), 
	pGameState(pGameState)
{
	this->Initalize(size_coefficient);
};
Stage::~Stage()
{};

void Stage::Initalize(const float size_coefficient)
{
	Lista<Entity*> colidiveis;

	sf::Vector2f position(0.f, (192 * size_coefficient) - RECT_SIZE - 36.f);
	float X_Coeff = 3.5f, Y_Coeff = X_Coeff / 2.f;
	int i = 0;

	sf::FloatRect bounds((352.f * size_coefficient * -2.f), (-192.f + 40.f), (352.f * size_coefficient * 2.f), (192.f * size_coefficient));
	
	std::list<Characters::Player*> players;
	for (i = 0; i < PLAYER_NUM; i++)
	{
		players.push_back(new Characters::Player(1.0f));
		players.front()->MovePosition(position + sf::Vector2f(-48.f * i, 0.f * i));
		
		this->entities.PushBack(static_cast<Entity*>(players.front()));
		colidiveis.PushBack(static_cast<Entity*>(players.front()));
	}

	std::list<Obstacles::Obstacle*> obstacles;
	for (int f = 0; f < 5; f++)
	{
		sf::RectangleShape obsSize(sf::Vector2f(OBSTACLE_SIZE, OBSTACLE_SIZE));

		obstacles.push_back(new Obstacles::Obstacle(
			obsSize, OBSTACLE_TEXTURE_REF,
			sf::IntRect(0, 0, OBSTACLE_SIZE, OBSTACLE_SIZE), 1.0f, false
		));
		obstacles.back()->MovePosition(sf::Vector2f(position.x + (obsSize.getSize().x * f), position.y + OBSTACLE_SIZE * 2.f));
		
		this->entities.PushBack(static_cast<Entity*>(obstacles.back()));
		colidiveis.PushBack(static_cast<Entity*>(obstacles.back()));
	}

	this->colision_manager.AddRange(&colidiveis);
	this->background.ResetPosition();
};
void Stage::InputHandle(const sf::Event& _event)
{
	unsigned int i = 0;

	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
		*this->pGameState = GameStateType::PAUSE_MENU;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		if (this->entities[i].GetInfo()->GetType() == Type::PLAYER)
		{
			static_cast<Characters::Player*>(this->entities[i].GetInfo())->InputHandle(_event);
		}
	}
};

void Stage::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	Lista<Entity*>::iterador it;

	this->background.SelfPrint(context_window, pElapsedTime);

	for(it = this->entities.begin(); it != this->entities.end(); it++)
		(*it)->SelfPrint(context_window, pElapsedTime);
};
void Stage::Execute(const float& pElapsedTime)
{
	unsigned int i = 0;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		this->entities[i].GetInfo()->Execute(pElapsedTime);
	}
	Manager::GraphicManager::UpdateCamera();

	this->colision_manager.UpdateColisions(pElapsedTime);
	this->background.Execute(pElapsedTime);
};
void Stage::ReadArchive(const std::string path)
{

};

void Stage::AddEntity(Entity* entity)
{
	if (entity == nullptr)
		return;

	this->entities.PushBack(entity);
	this->colision_manager.Add(static_cast<Entity*>(entity));

	this->entities.SortElements();
};
void Stage::AddRange(std::list<Entity*>* _entities)
{
	std::list<Entity*>::iterator it;

	if (_entities == nullptr)
		return;

	for(it = _entities->begin(); it != _entities->end(); it++)
	{
		this->entities.PushBack(*it);
		this->colision_manager.Add(static_cast<Entity*>(*it));
	}

	this->entities.SortElements();
};
void Stage::RemoveEntity(const unsigned long long int entityId)
{
	Lista<Entity*>::iterador it;

	for(it = this->entities.begin(); it != this->entities.end(); it++)
	{
		if((*it)->GetId() == entityId)
			this->entities.PopAt(it);
	}

	this->colision_manager.Remove(entityId);
	this->entities.SortElements();
};
void Stage::RemoveRange(const std::vector<unsigned long long int> entityId)
{
	std::vector<unsigned long long int>::const_iterator cIt;
	Lista<Entity*>::iterador it;

	for (cIt = entityId.cbegin(); cIt != entityId.cend(); cIt++)
	{
		for (it = this->entities.begin(); it != this->entities.end(); ++it)
		{
			if ((*it)->GetId() == (*cIt))
				this->entities.PopAt(it);

			this->colision_manager.Remove(*cIt);
		}
	}

	this->entities.SortElements();
};

void Stage::AddPlayer()
{};
void Stage::RemovePlayer()
{};