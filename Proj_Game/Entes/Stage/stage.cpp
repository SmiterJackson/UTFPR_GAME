#include "stage.h"
#include "../game/game.h"
using namespace Manager;
using namespace Trait;

#define NUM_BCKG_INSTANCES 3U

#define RECT_SIZE 50.f

#define OBSTACLE_TEXTURE_REF "Proj_Game/Resources/tile_sets/Texture/TX_Tileset_Ground.png"
#define OBSTACLE_SIZE 32

#define PLAYER_NUM 1

Stage::Parallax::Parallax(const std::vector<std::string>& paths, const float _size_coeff) :
	Ente(Type::BACKGROUND, PrintPriority::background),
	backGrounds(),
	lastPosition(0.f, 0.f), layers_spd_coeff(1.f), size_coeff(_size_coeff)
{
	this->SetBackgrounds(paths);
};
Stage::Parallax::~Parallax()
{};

void Stage::Parallax::SetBackgrounds(const std::vector<std::string>& paths)
{
	std::vector<std::string>::const_iterator cIt;
	std::vector<sf::Sprite>* pLastSpriteVec = nullptr;
	sf::Sprite* pLastSprite = nullptr;
	sf::Texture* txt = nullptr;
	size_t i = 0;

	if (this->backGrounds.size() > 0)
		this->backGrounds.clear();

	/*
		Para cada path de textura para efeito parallax cria 2 objetos de 'Background' subsequentes em ordem na
		lista e em posição na tela, tal que, cada qual com o tamanho equilavente à 2 vezes a própria textura,
		efetivando o efeito de 4 texturas iguais em fila plotados na tela
	*/
	this->backGrounds.reserve(paths.size());
	for (cIt = paths.cbegin(); cIt != paths.cend(); cIt++)
	{
		txt = Manager::GraphicManager::LoadTexture(*cIt);
		this->backGrounds.emplace_back(Layer(txt, std::vector<sf::Sprite>()));
		pLastSpriteVec = &this->backGrounds.back().second;

		pLastSpriteVec->reserve(NUM_BCKG_INSTANCES);
		for (i = 0; i < NUM_BCKG_INSTANCES; i++)
		{
			pLastSpriteVec->emplace_back(sf::Sprite());
			pLastSprite = &pLastSpriteVec->back();

			pLastSprite->setTexture(*txt);
			pLastSprite->setScale(this->size_coeff, this->size_coeff);
			pLastSprite->move((txt->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->layers_spd_coeff = 1.f / this->backGrounds.size();
	this->lastPosition = GraphicManager::GetView()->getCenter();
};
void Stage::Parallax::ResetBackground()
{
	std::vector<Layer>::iterator layer;
	std::vector<sf::Sprite>::iterator SpriteIt;
	unsigned int i = 0;

	for (layer = this->backGrounds.begin(); layer != this->backGrounds.end(); layer++)
	{
		for (i = 0, SpriteIt = layer->second.begin(); SpriteIt != layer->second.end(); SpriteIt++, i++)
		{
			SpriteIt->setPosition(0.f, 0.f);
			SpriteIt->move((layer->first->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->lastPosition = GraphicManager::GetView()->getCenter();
};

void Stage::Parallax::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	std::vector<Layer>::reverse_iterator rIt;
	size_t i = 0;

	for (rIt = this->backGrounds.rbegin(); rIt != this->backGrounds.rend(); rIt++)
		for (i = 0; i < rIt->second.size(); i++)
			context_window.draw(rIt->second[i]);
};
void Stage::Parallax::Execute(const float& pElapsedTime)
{
	std::vector<Layer>::iterator it;
	sf::Sprite* pSprite = nullptr;
	sf::Vector2f diff, movement;
	float leastLim = 0.f, maxLim = 0.f, counter = 1.f;
	unsigned int i = 0;

	if (GraphicManager::GetView() != nullptr)
	{
		diff = this->lastPosition - GraphicManager::GetView()->getCenter();
		leastLim = GraphicManager::GetView()->getCenter().x - GraphicManager::GetView()->getSize().x;
		maxLim = GraphicManager::GetView()->getCenter().x + GraphicManager::GetView()->getSize().x;
		this->lastPosition = GraphicManager::GetView()->getCenter();
	}

	/*
		Para a quantidade de "layers", camadas, de backgrounds em função do número de cópias/instancias,
		move cada camada proporcinalmente a sua respectiva velocidade dado pela "posição da camada"
	*/
	if (diff.x != 0.f || diff.y != 0.f)
	{
		for (it = this->backGrounds.begin(), counter = 0;
			it != this->backGrounds.end();
			counter++, it++)
		{
			movement = diff * (-layers_spd_coeff * counter);

			for (i = 0; i < it->second.size(); i++)
			{
				pSprite = &it->second[i];

				pSprite->move(movement);

				if (pSprite->getPosition().x + pSprite->getGlobalBounds().width < leastLim)
					pSprite->move((pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);

				else if (pSprite->getPosition().x > maxLim)
					pSprite->move(-(pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);
			}
		}
	}
};



Stage::Stage():
	Interface(GameStateType::IN_GAME),
	worldBounds(),
	colision_manager(*this),
	background(),
	entities()
{
	this->Initalize(1.f);
};
Stage::Stage(const sf::FloatRect bounds, const std::string& stagePath,
			 const std::vector<std::string>& BackgroundPaths, const float size_coefficient):
	Interface(GameStateType::IN_GAME),
	worldBounds(bounds.left, bounds.top, bounds.width, bounds.height /* + 200.f*/),
	colision_manager(*this),
	background(BackgroundPaths, size_coefficient),
	entities()
{
	GraphicManager::SetCameraLimits(bounds);

	this->Initalize(size_coefficient);

	GraphicManager::UpdateCamera();
	this->background.ResetBackground();
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
		sf::Vector2f obsSize(OBSTACLE_SIZE, OBSTACLE_SIZE);

		obstacles.push_back(new Obstacles::Obstacle(
			obsSize, sf::Vector2f(0.f,0.f), OBSTACLE_TEXTURE_REF,
			sf::IntRect(0, 0, OBSTACLE_SIZE, OBSTACLE_SIZE), 1.0f, true, false
		));
		obstacles.back()->MovePosition(sf::Vector2f(position.x + (obsSize.x * f), position.y + OBSTACLE_SIZE * 2.f));
		
		this->entities.PushBack(static_cast<Entity*>(obstacles.back()));
		colidiveis.PushBack(static_cast<Entity*>(obstacles.back()));
	}
	this->colision_manager.AddRange(&colidiveis);
};
void Stage::InputHandle(const sf::Event& _event)
{
	unsigned int i = 0;

	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
		Game::SetGameState(GameStateType::PAUSE_MENU);

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