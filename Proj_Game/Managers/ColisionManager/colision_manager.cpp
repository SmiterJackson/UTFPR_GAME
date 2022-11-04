#include "colision_manager.h"
#include "../GraphicManager/graphic_manager.h"
#include "../Entes/Stage/stage.h"
using namespace Manager;

#define OFFSET sf::Vector2f(0.f, 0.001f)
#define COLISION_CHECK_TIMER 0.2f

ColisionManager::ColisionManager(Stage& stage, Lista<Entity*>* _pEntities):
	entities(), stageRef(stage), accumulator(0.f)
{
	Lista<Entity*>::iterador it;

	if (_pEntities != nullptr)
	{
		this->entities.reserve(_pEntities->GetSize());
		for (it = _pEntities->begin(); it != _pEntities->end(); ++it)
		{
			this->entities.emplace_back(*it);
		}
	}
};
ColisionManager::~ColisionManager()
{};

void ColisionManager::UpdateColisions(const float& pElapsedTime)
{
	ColisonVector::iterator ente;
	ColisonVector::iterator otherEnt;
	ColisonVector camVector;
	this->accumulator += pElapsedTime;

	if (this->accumulator >= COLISION_CHECK_TIMER)
	{
		// Verifica colisões apenas entre entidades proximas a camera
		camVector = GraphicManager::GetCameraEntities(this->entities);

		for (ente = camVector.begin(); ente != camVector.end(); ente++)
		{
			for (otherEnt = camVector.begin(); otherEnt != camVector.end(); otherEnt++)
			{
				// Evita comparar o objeto consigo mesmo e entre classes de mesmo tipo, bem como entre elementos estáticos
				if(	ente != otherEnt 
				&&	(*ente)->GetType() != (*otherEnt)->GetType() 
				&&	((*ente)->GetIfStatic() || (*otherEnt)->GetIfStatic()))
					this->CheckInColision(*ente, *otherEnt);
			}

			if(!(*ente)->GetIfStatic())
				this->CheckOfColision(*ente);
		}

		this->accumulator -= pElapsedTime;
	}
};

void ColisionManager::Add(Entity* entity)
{
	entities.emplace_back(entity);
};
void ColisionManager::AddRange(Lista<Entity*>* _entities)
{
	Lista<Entity*>::iterador it;

	if (_entities != nullptr)
	{
		for (it = _entities->begin(); it != _entities->end(); ++it)
		{
			this->entities.emplace_back(*it);
		}
	}
};
void ColisionManager::Remove(const unsigned long long int entityId)
{
	ColisonVector::const_iterator cIt;

	for (cIt = this->entities.cbegin(); cIt != this->entities.cend(); cIt++)
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
	ColisonVector::const_iterator cIt;

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
	}
};

void ColisionManager::CheckInColision(Entity* entity, Entity* other)
{
	// Aplica-se o offset para verificar se há uma plataforma abaixo da entidade
	sf::Vector2f distance(entity->GetPosition() - other->GetPosition() + OFFSET);
	sf::Vector2f entSize(entity->GetHitBoxSize() / 2.f);
	sf::Vector2f otherSize(other->GetHitBoxSize() / 2.f);
	sf::Vector2f intersection(
		fabs(distance.x) - (entSize.x + otherSize.x),
		fabs(distance.y) - (entSize.y + otherSize.y)
	);

	if (intersection.x < 0.f && intersection.y < 0.f)
	{
		entity->Collided(other, intersection, other->GetBounds(), CollisionType::EntityColl);
		other->Collided(entity, intersection, entity->GetBounds(), CollisionType::EntityColl);
	}
};
void ColisionManager::CheckOfColision(Entity* entity)
{
	sf::FloatRect cameraBounds(Manager::GraphicManager::GetViewBounds());
	sf::FloatRect stageBounds(this->stageRef.GetBounds());
	sf::FloatRect bounds(entity->GetBounds());

	if (bounds.left < cameraBounds.left || bounds.width > cameraBounds.width)
		entity->Collided(nullptr, sf::Vector2f(), cameraBounds, CollisionType::CameraColl);

	if (bounds.left < stageBounds.left	|| bounds.width		> stageBounds.width ||
		bounds.top	< stageBounds.top	|| bounds.height	> stageBounds.height)
		entity->Collided(nullptr, sf::Vector2f(), stageBounds, CollisionType::MapColl);
};

void ColisionManager::SortElements()
{
	QuickSortRecursion(0, this->entities.size() - 1);
};
void ColisionManager::QuickSortRecursion(unsigned int start, unsigned int end)
{
	unsigned int pivotIndex = 0;

	if (start >= end)
		return;

	pivotIndex = SortPartition(start, end);

	QuickSortRecursion(start, pivotIndex - 1);
	QuickSortRecursion(pivotIndex + 1, end);
};
unsigned int ColisionManager::SortPartition(unsigned int start, unsigned int end)
{
	ColisonVector::iterator it;
	unsigned int pivotValue = 0, pivotIndex = 0, i = 0;
	unsigned int diff = end - start;

	if (diff > 1) 
	{
		pivotIndex = Mediana(
			this->entities[start]->GetType(),				// primeiro item do recorte da lista
			this->entities[start + (diff / 2)]->GetType(),	// item do meio do recorte da lista
			this->entities[end]->GetType()					// último item do recorte da lista
		);
		ExchangePointers(&this->entities[pivotIndex], &this->entities[end]);
	}

	pivotValue = this->entities[end]->GetType();
	for (i = start, pivotIndex = start; i < end; i++)
	{
		if (this->entities[i]->GetType() <= pivotValue)
		{
			ExchangePointers(&this->entities[i], &this->entities[pivotIndex]);
			pivotIndex++;
		}
	}
	if (this->entities[end] != this->entities[pivotIndex])
		ExchangePointers(&this->entities[end], &this->entities[pivotIndex]);

	return pivotIndex;
};

unsigned int ColisionManager::Mediana(unsigned int val_1, unsigned int val_2, unsigned int val_3)
{
	unsigned int median = 0;

	// Retorna o maior valor entre 1 e 2
	median = ((val_1 > val_2) * val_1) + ((val_1 < val_2) * val_2);

	// Retorna o menor valor entre 2 e 3
	median = ((median < val_3) * median) + ((median > val_3) * val_3);

	return median;
};
void ColisionManager::ExchangePointers(Entity** p1, Entity** p2)
{
	Entity* aux = nullptr;

	if(p1 != nullptr && p2 != nullptr)
	{
		aux = *p1;
		*p1 = *p2;
		*p2 = aux;
	}
};