#include "colision_manager.h"
#include "../game/game.h"
#include "../GraphicManager/graphic_manager.h"
#include "../Entes/GUI/Interfaces/Stage/stage.h"
using namespace Manager;
using namespace GUI;

#define OFFSET sf::Vector2f(0.f, 0.001f)
#define COLISION_CHECK_TIMER 0.2f

ColisionManager* ColisionManager::instance = nullptr;

ColisionManager* ColisionManager::GetInstance(Lista<Entity*>* _pEntities)
{
	if(instance == nullptr)
	{
		instance = new ColisionManager(_pEntities);
		if (instance == nullptr)
			std::cerr << "Nao foi possivel instanciar um gerenciador de colisoes." << std::endl;
	}

	return instance;
};
void ColisionManager::DeconstructInstance()
{
	if (instance == nullptr)
		delete instance;
};

ColisionManager::ColisionManager(Lista<Entity*>* _pEntities):
	entities(), staticEntities(), accumulator(0.f)
{
	Lista<Entity*>::Iterador it;

	if (_pEntities != nullptr)
	{
		for (it = _pEntities->begin(); it != _pEntities->end(); ++it)
		{
			if((*it)->IsStatic())
				this->staticEntities.emplace_back(*it);
			else
				this->entities.emplace_back(*it);
		}
	}
};
ColisionManager::~ColisionManager()
{};

void ColisionManager::UpdateColisions(const float& pElapsedTime)
{
	Entities camEntities;
	Entities camStaticEntities;
	Entities::iterator ente;
	Entities::iterator otherEnt;

	this->accumulator += pElapsedTime;

	if (this->accumulator >= COLISION_CHECK_TIMER)
	{
		// Verifica colis�es apenas entre entidades proximas a camera
		camEntities = GraphicManager::GetCameraEntities(this->entities);
		camStaticEntities = GraphicManager::GetCameraEntities(this->staticEntities);

		for (ente = camEntities.begin(); ente != camEntities.end(); ente++)
		{
			// Compara objetos est�ticos com n�o est�ticos
			for (otherEnt = camStaticEntities.begin(); otherEnt != camStaticEntities.end(); otherEnt++)
				this->CheckInColision(*ente, *otherEnt);

			for (otherEnt = camEntities.begin(); otherEnt != camEntities.end(); otherEnt++)
			{
				// Evita comparar o objeto consigo mesmo e entre classes de mesmo tipo
				if(	ente != otherEnt &&	(*ente)->GetType() != (*otherEnt)->GetType())
					this->CheckInColision(*ente, *otherEnt);
			}

			this->CheckOfColision(*ente);
		}

		this->accumulator -= pElapsedTime;
	}
};

void ColisionManager::Add(Entity* entity)
{
	if (entity->IsStatic())
		this->staticEntities.emplace_back(entity);
	else
		this->entities.emplace_back(entity);
};
void ColisionManager::AddRange(Lista<Entity*>* _entities)
{
	Lista<Entity*>::Iterador it;

	if (_entities != nullptr)
	{
		for (it = _entities->begin(); it != _entities->end(); ++it)
		{
			if ((*it)->IsStatic())
				this->staticEntities.emplace_back(*it);
			else
				this->entities.emplace_back(*it);
		}
	}
};
void ColisionManager::Remove(const unsigned long long int entityId)
{
	Entities::const_iterator cIt;

	for (cIt = this->entities.cbegin(); cIt != this->entities.cend(); cIt++)
	{
		if ((*cIt)->GetId() == entityId)
		{
			this->entities.erase(cIt);
			break;
		}
	};
	for (cIt = this->staticEntities.cbegin(); cIt != this->staticEntities.cend(); cIt++)
	{
		if ((*cIt)->GetId() == entityId)
		{
			this->entities.erase(cIt);
			break;
		}
	};
};
void ColisionManager::RemoveRange(const std::vector<unsigned long long int> entitiesIds)
{
	std::vector<unsigned long long int>::const_iterator idCit;
	Entities::const_iterator cIt;

	for(idCit = entitiesIds.cbegin(); idCit != entitiesIds.cend(); idCit++)
	{
		for (cIt = this->entities.cbegin(); cIt != this->entities.cend(); cIt++)
		{
			if ((*cIt)->GetId() == *idCit)
			{
				this->entities.erase(cIt);
				break;
			}
		};
		for (cIt = this->staticEntities.cbegin(); cIt != this->staticEntities.cend(); cIt++)
		{
			if ((*cIt)->GetId() == *idCit)
			{
				this->entities.erase(cIt);
				break;
			}
		};
	}
};

void ColisionManager::CheckInColision(Entity* entity, Entity* other)
{
	// Aplica-se o offset para verificar se h� uma plataforma abaixo da entidade
	sf::Vector2f distance(entity->GetPosition() - other->GetPosition() + OFFSET);
	sf::Vector2f entRadious(entity->GetSize() / 2.f);
	sf::Vector2f otherRadious(other->GetSize() / 2.f);
	sf::Vector2f intersection(
		fabs(distance.x) - (entRadious.x + otherRadious.x),
		fabs(distance.y) - (entRadious.y + otherRadious.y)
	);

	if (intersection.x < 0.f && intersection.y < 0.f)
	{
		entity->Collided(other, intersection, CollisionType::EntityColl);
		other->Collided(entity, intersection, CollisionType::EntityColl);
	}
};
void ColisionManager::CheckOfColision(Entity* entity)
{
	sf::Vector2f camRadious(GraphicManager::GetViewSize() / 2.f);
	sf::Vector2f stageRadious(Stage::GetWorldSize() / 2.f);
	sf::Vector2f radious(entity->GetSize() / 2.f);
	sf::Vector2f intersection(0.f, 0.f);
	sf::Vector2f distance(
		entity->GetPosition().x - Stage::GetWorldPosition().x,
		entity->GetPosition().y - Stage::GetWorldPosition().y
	);

	intersection = sf::Vector2f(
		fabs(distance.x) - (stageRadious.x - radious.x),
		fabs(distance.y) - (stageRadious.y - radious.y)
	);
	if (intersection.x > 0.f || intersection.y > 0.f)
	{
		if (intersection.x <= 0.f)
			intersection.x = 0.f;

		if (intersection.y <= 0.f)
			intersection.y = 0.f;

		if (distance.x > 0.f)
			intersection.x = -(intersection.x);

		if (distance.y > 0.f)
			intersection.y = -(intersection.y);

		entity->Collided(nullptr, intersection, CollisionType::MapColl);
	}

	distance = sf::Vector2f(
		entity->GetPosition().x - GraphicManager::GetViewPosition().x,
		entity->GetPosition().y - GraphicManager::GetViewPosition().y
	);
	intersection = sf::Vector2f(
		fabs(distance.x) - (camRadious.x - radious.x),
		fabs(distance.y) - (camRadious.y - radious.y)
	);
	if (intersection.x > 0.f || intersection.y > 0.f)
	{ 
		if (intersection.x <= 0.f)
			intersection.x = 0.f;

		if (intersection.y <= 0.f)
			intersection.y = 0.f;

		if (distance.x > 0.f)
			intersection.x = -(intersection.x);

		if (distance.y > 0.f)
			intersection.y = -(intersection.y);

		entity->Collided(nullptr, intersection, CollisionType::CameraColl);
	}
};