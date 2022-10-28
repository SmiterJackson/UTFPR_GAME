#include "stage.h"

#define RECT_SIZE 50.f

#define OBSTACLE_TEXTURE_REF "Proj_Game/Resources/tile_sets/Texture/TX_Tileset_Ground.png"
#define OBSTACLE_SIZE 32

Stage::Stage():
	Ente(Ente::STAGE, nullptr), mapBounds(), colision_manager(), background(), pCamera(nullptr), entities(), pGameState(nullptr)
{
	this->Initalize(1.f);
};
Stage::Stage(short int* _pGameState, Camera* camera, float* pElapsedTime, sf::FloatRect _mapBounds, const std::string& stagePath,
			 const std::vector<std::string>& BackgroundPaths, const float size_coefficient):
	Ente(Ente::STAGE, pElapsedTime), mapBounds(_mapBounds), colision_manager(this, camera, pElapsedTime),
	background(camera->GetView(), pElapsedTime, BackgroundPaths, size_coefficient), pCamera(camera), entities(), pGameState(_pGameState)
{
	this->Initalize(size_coefficient);
};
Stage::~Stage()
{};

void Stage::Initalize(const float size_coefficient)
{
	sf::Vector2f position(0.f, (192 * size_coefficient) - RECT_SIZE - 36.f);
	float X_Coeff = 3.5f, Y_Coeff = X_Coeff / 2.f;

	sf::FloatRect bounds((352.f * size_coefficient * -2.f), (-192.f + 40.f), (352.f * size_coefficient * 2.f), (192.f * size_coefficient));

	std::list<Characters::Player*> players;
	players.push_back(new Characters::Player(this->elapsedTime, 1.0f));
	players.front()->MovePosition(position);
	this->entities.PushBack(static_cast<Ente*>(players.front()));

	/*players.emplace_back(new Characters::Player(this->elapsedTime));
	players.back()->MovePosition(position + sf::Vector2f(-48.f, 0.f));
	this->entities.PushBack(static_cast<Ente*>(players.back()));*/

	this->pCamera->AddPlayerRange(&players);

	std::list<Obstacles::Obstacle*> obstacles;
	for (int f = 0; f < 20; f++)
	{
		obstacles.push_back(new Obstacles::Obstacle(
			this->elapsedTime, sf::RectangleShape(sf::Vector2f(OBSTACLE_SIZE, OBSTACLE_SIZE)),
			OBSTACLE_TEXTURE_REF, sf::IntRect(0, 0, OBSTACLE_SIZE, OBSTACLE_SIZE), 1.0f
		));
		obstacles.back()->MovePosition(sf::Vector2f(position.x + (-OBSTACLE_SIZE * f), position.y + OBSTACLE_SIZE * 2.f));
		this->entities.PushBack(static_cast<Ente*>(obstacles.back()));
	}

	this->colision_manager.AddRange(&this->entities);
	this->background.ResetPosition();
};
void Stage::InputHandle(const sf::Event& _event)
{
	unsigned int i = 0;

	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
		*this->pGameState = Game::PAUSED;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		if (this->entities[i].GetInfo()->GetType() == Ente::CHARACTER)
		{
			static_cast<Characters::Player*>(this->entities[i].GetInfo())->InputHandle(_event);
		}
	}
};

void Stage::AddPlayer()
{
	Lista<Ente*>::iterador it;
	Characters::Player* auxPlayer = nullptr;
	Characters::Player* newPlayer = nullptr;
	unsigned int counter = 0;

	for(it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		if((*it)->GetId() == Ente::CHARACTER)
			counter++;

		if ((*it)->GetId() == Ente::CHARACTER && counter == 1)
			auxPlayer = static_cast<Characters::Player*>(*it);
	}

	if (counter < 2)
	{
		newPlayer = new Characters::Player(this->elapsedTime, 1.0f);
		if (newPlayer != nullptr && auxPlayer != nullptr)
		{
			newPlayer->MovePosition(auxPlayer->GetPosition());

			this->pCamera->AddPlayer(newPlayer);
			this->entities.PushBack(static_cast<Ente*>(newPlayer));
			this->colision_manager.Add(static_cast<Entity*>(newPlayer));
		}
		else
			std::cout << "Nao foi possivel alocar outro player." << std::endl;
	}
};
void Stage::RemovePlayer()
{
	Lista<Ente*>::iterador it;
	unsigned int counter = 0;

	for (it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		if ((*it)->GetId() == Ente::CHARACTER)
			counter++;

		if (counter == 2)
			break;
	}

	this->entities.PopAt(it);
};

void Stage::AddEntity(Ente* entity)
{
	if (entity == nullptr)
		return;

	this->entities.PushBack(entity);
};
void Stage::AddRange(std::list<Ente*>* _entities)
{
	std::list<Ente*>::iterator it;

	if (_entities == nullptr)
		return;

	for(it = _entities->begin(); it != _entities->end(); it++)
	{
		this->entities.PushBack(*it);
	}
};
void Stage::AddRange(std::vector<Ente*>* _entities)
{
	std::vector<Ente*>::iterator it;

	if (_entities == nullptr)
		return;

	for (it = _entities->begin(); it != _entities->end(); it++)
	{
		this->entities.PushBack(*it);
	}
};
void Stage::RemoveEntity(const unsigned int entityId)
{
	this->entities.PopAt(entityId);
};

void Stage::Execute()
{
	unsigned int i = 0;

	for (i = 0; i < this->entities.GetSize(); i++)
	{
		this->entities[i].GetInfo()->Execute();
	}

	this->colision_manager.UpdateColisions();
	this->background.Execute();
};
void Stage::SelfPrint(sf::RenderWindow& context_window)
{
	Lista<Ente*>::iterador it;

	this->background.SelfPrint(context_window);

	for (it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		(*it)->SelfPrint(context_window);
	}
};
void Stage::ReadArchive(const std::string path)
{

};