#include "colisionManager.h"

#define COLISION_CHECK_TIMER 0.2f

ColisionManager::ColisionManager() :
	entities(), mapBorders(), cameraRef(nullptr), elaps_accumul(0.f), pElapsedTime(nullptr)
{};
ColisionManager::ColisionManager(Camera* pCamera, const sf::FloatRect _mapBorders, float* pElapsedTime, std::list<Entity*>* _entities) :
	entities(), mapBorders(), cameraRef(pCamera), elaps_accumul(0.f), pElapsedTime(pElapsedTime)
{
	std::list<Entity*>::iterator it;

	if (_entities != nullptr)
	{
		for (it = (*_entities).begin(); it != (*_entities).end(); it++)
		{
			entities.emplace_back((*it));
		};

		this->SortElements();
	}
};
ColisionManager::ColisionManager(Camera* pCamera, const sf::FloatRect _mapBorders, float* pElapsedTime, std::vector<Entity*>* _entities) :
	entities(), mapBorders(), cameraRef(pCamera), elaps_accumul(0.f), pElapsedTime(pElapsedTime)
{
	std::vector<Entity*>::iterator it;

	if (_entities != nullptr)
	{
		for (it = (*_entities).begin(); it != (*_entities).end(); it++)
		{
			entities.emplace_back((*it));
		};

		this->SortElements();
	}
};
ColisionManager::~ColisionManager()
{};

void ColisionManager::UpdateColisions()
{
	std::vector<Entity*>::iterator itEnte;
	std::vector<Entity*>::iterator itOther;
	std::vector<Entity*> camVector;
	elaps_accumul += *this->pElapsedTime;

	if (COLISION_CHECK_TIMER <= elaps_accumul)
	{
		// Verifica colisões apenas entre entidades proximas a camera
		camVector = this->cameraRef->GetCameraEntities(&this->entities);

		for (itEnte = camVector.begin(); itEnte != camVector.end(); itEnte++)
		{
			//	Evita comparar colisões entre obstaculos
			if ((*itEnte)->GetType() != Ente::OBSTACLE)
			{
				for (itOther = camVector.begin(); itOther != camVector.end(); itOther++)
				{
					// Evita comparar o objeto consigo mesmo e colisão entre dois players (nada emplementado nesse sentido)
					if(itEnte != itOther && (*itOther)->GetId() != Ente::CHARACTER)
					{
						CheckColision((*itEnte), (*itOther));
					}
				}

				if ((*itEnte)->GetType() == Ente::CHARACTER)
					CheckOutOfCamera((*itEnte));
			}
		}

		elaps_accumul -= *this->pElapsedTime;
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
	
	entSize /= 2.0f;
	otherSize /= 2.0f;

	intersection = sf::Vector2f(
		fabs(distance.x) - (entSize.x + otherSize.x),
		fabs(distance.y) - (entSize.y + otherSize.y)
	);

	if(intersection.x < 0.f && intersection.y < 0.f)
	{
		entity->Collided(other);
		other->Collided(entity);
	}
};
void ColisionManager::CheckOutOfCamera(Entity* entity)
{
	sf::FloatRect cameraBounds(this->cameraRef->CameraBounds());
	sf::FloatRect entBounds(entity->GetHitBoxBounds());

	if (entBounds.left < cameraBounds.left || entBounds.width > cameraBounds.width)
	{
		if (entBounds.left < cameraBounds.left)
			entity->MovePosition(sf::Vector2f(cameraBounds.left - entBounds.left, 0.f));
		else
			entity->MovePosition(sf::Vector2f(cameraBounds.width - entBounds.width, 0.f));
	}
};

void ColisionManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);
};
void ColisionManager::AddRange(std::list<Entity*>* _entities)
{
	std::list<Entity*>::iterator it;

	if (_entities != nullptr)
	{
		for(it = (*_entities).begin(); it != (*_entities).end(); it++)
		{
			this->entities.emplace_back((*it));
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
			this->entities.emplace_back((*it));
		}
	}
};
void ColisionManager::RemoveEntity(const unsigned int entityId)
{
	std::vector<Entity*>::const_iterator cIt;

	for (cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
	{
		if ((*cIt)->GetId() == entityId)
		{
			entities.erase(cIt);
			break;
		}
	};
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