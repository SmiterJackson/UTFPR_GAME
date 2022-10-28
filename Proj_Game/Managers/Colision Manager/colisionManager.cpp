#include "colisionManager.h"
#include "../../Entities/StageClass/stage.h"

#define OFFSET sf::Vector2f(0.f, 0.001f)
#define COLISION_CHECK_TIMER 0.2f

ColisionManager::ColisionManager() :
	entities(), stageRef(nullptr), cameraRef(nullptr), elaps_accumul(0.f), pElapsedTime(nullptr)
{};
ColisionManager::ColisionManager(Stage* pStage, Camera* pCamera, float* pElapsedTime, Lista<Ente*>* _pEntities) :
	entities(), stageRef(pStage), cameraRef(pCamera), elaps_accumul(0.f), pElapsedTime(pElapsedTime)
{
	Lista<Ente*>::iterador it;

	if (_pEntities != nullptr)
	{
		for (it = _pEntities->begin(); it != _pEntities->end(); ++it)
		{
			if ((*it)->GetType() != Ente::UNDEFINED		&&
				(*it)->GetType() != Ente::STAGE			&&
				(*it)->GetType() != Ente::BACKGROUND	&&
				(*it)->GetType() != Ente::CAMERA		)
			{
				this->entities.emplace_back(static_cast<Entity*>(*it));
			}
		}
	}
};
ColisionManager::~ColisionManager()
{};

void ColisionManager::UpdateColisions()
{
	std::vector<Entity*>::iterator itEnte;
	std::vector<Entity*>::iterator itOther;
	std::vector<Entity*> camVector;
	this->elaps_accumul += *this->pElapsedTime;

	if (this->elaps_accumul >= COLISION_CHECK_TIMER)
	{
		// Verifica colisões apenas entre entidades proximas a camera
		camVector = this->cameraRef->GetCameraEntities(&this->entities);

		for (itEnte = camVector.begin(); itEnte != camVector.end(); itEnte++)
		{
			for (itOther = camVector.begin(); itOther != camVector.end(); itOther++)
			{
				// Evita comparar o objeto consigo mesmo e entre classes de mesmo tipo
				if(itEnte != itOther && (*itEnte)->GetId() != (*itOther)->GetId())
				{
					this->CheckColision((*itEnte), (*itOther));
				}
			}

			if ((*itEnte)->GetType() == Ente::CHARACTER)
				this->CheckOutOfCamera((*itEnte));

			this->CheckOutOfMap((*itEnte));
		}

		this->elaps_accumul -= *this->pElapsedTime;
	}
};
void ColisionManager::CheckColision(Entity* entity, Entity* other)
{
	sf::Vector2f intersection;
	sf::Vector2f entSize(entity->GetHitBoxSize());
	sf::Vector2f otherSize(other->GetHitBoxSize());
	sf::Vector2f distance(
		entity->GetPosition().x - other->GetPosition().x,
		entity->GetPosition().y - other->GetPosition().y
	);

	// Aplica-se o offset para verificar se há uma plataforma abaixo da entidade
	distance += OFFSET;

	entSize /= 2.0f;
	otherSize /= 2.0f;

	intersection = sf::Vector2f(
		fabs(distance.x) - (entSize.x + otherSize.x),
		fabs(distance.y) - (entSize.y + otherSize.y)
	);

	if(intersection.x < 0.f && intersection.y < 0.f)
	{
		entity->Collided(static_cast<Ente*>(other));
		other->Collided(static_cast<Ente*>(entity));
	}
};
void ColisionManager::CheckOutOfCamera(Entity* entity)
{
	sf::FloatRect cameraBounds(this->cameraRef->CameraBounds());
	sf::FloatRect entBounds(entity->GetHitBoxBounds());

	if (entBounds.left < cameraBounds.left || entBounds.width > cameraBounds.width)
		entity->Collided(static_cast<Ente*>(this->cameraRef));
};
void ColisionManager::CheckOutOfMap(Entity* entity)
{
	sf::FloatRect entBounds(entity->GetHitBoxBounds());
	sf::FloatRect mapBounds(this->stageRef->GetMapBounds());

	entBounds.height += OFFSET.y;

	if (entBounds.top < mapBounds.top || entBounds.height > mapBounds.height)
	{
		entity->Collided(static_cast<Ente*>(this->stageRef));
	}
};

void ColisionManager::Add(Entity* entity)
{
	entities.emplace_back(entity);
};
void ColisionManager::AddRange(Lista<Ente*>* _entities)
{
	Lista<Ente*>::iterador it;

	if (_entities != nullptr)
	{
		for (it = _entities->begin(); it != _entities->end(); ++it)
		{
			if ((*it)->GetType() != Ente::UNDEFINED &&
				(*it)->GetType() != Ente::STAGE &&
				(*it)->GetType() != Ente::BACKGROUND &&
				(*it)->GetType() != Ente::CAMERA)
			{
				this->entities.emplace_back(static_cast<Entity*>(*it));
			}
		}
	}
};
void ColisionManager::AddRange(std::vector<Entity*>* _entities)
{
	std::vector<Entity*>::iterator it;

	if (_entities != nullptr)
	{
		for (it = (*_entities).begin(); it != (*_entities).end(); it++)
		{
			if ((*it)->GetType() != Ente::UNDEFINED &&
				(*it)->GetType() != Ente::STAGE &&
				(*it)->GetType() != Ente::BACKGROUND &&
				(*it)->GetType() != Ente::CAMERA)
			{
				this->entities.emplace_back((*it));
			}
		}
	}
};
void ColisionManager::Remove(const unsigned int entityId)
{
	std::vector<Entity*>::const_iterator cIt;

	for (cIt = this->entities.cbegin(); cIt != this->entities.cend(); cIt++)
	{
		if ((*cIt)->GetId() == entityId)
		{
			this->entities.erase(cIt);
			break;
		}
	};
};
void ColisionManager::RemoveRange(const std::vector<unsigned int> entitiesIds)
{
	std::vector<unsigned int>::const_iterator idCit;
	std::vector<Entity*>::const_iterator cIt;

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
	std::vector<Entity*>::iterator it;
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