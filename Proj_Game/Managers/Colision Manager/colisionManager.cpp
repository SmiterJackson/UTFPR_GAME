#include "colisionManager.h"

#define COLISION_CHECK_TIMER 0.1f

/*ColisionManager::ColisionManager() :
	entities(), mapBorders(), elapsTime_accumulator(0.f)
{};
ColisionManager::ColisionManager(const sf::FloatRect _mapBorders, const std::list<Entity*>& _entities) :
	entities(), mapBorders(), elapsTime_accumulator(0.f)
{
	std::list<Entity*>::const_iterator cIt;

	for (cIt = _entities.cbegin(); cIt != _entities.cend(); cIt++)
	{
		entities.emplace_back(*cIt);
	};
	entities.sort();
};
ColisionManager::~ColisionManager()
{};

void ColisionManager::AddEntity(const Entity* entity)
{
	std::list<Entity*>::const_iterator cIt;

	for (cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
	{
		if ((*cIt)->GetType() >= entity->GetType())
		{
			entities.emplace(cIt, entity);
			break;
		}
	};
};
void ColisionManager::RemoveEntity(const unsigned int entityId)
{
	std::list<Entity*>::const_iterator cIt;

	for (cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
	{
		if ((*cIt)->GetId() == entityId)
		{
			entities.erase(cIt);
			break;
		}
	};
};
void ColisionManager::CheckColisions(const float elapsedTime)
{
	std::list<Entity*>::const_iterator cIt;
	elapsTime_accumulator += elapsedTime;

	if (COLISION_CHECK_TIMER <= elapsTime_accumulator)
	{
		for(cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
		{
			if ((*cIt)->GetType() == Ente::CHARACTER || (*cIt)->GetType() == Ente::PROJECTILE)
			{
				
			}
		}

		elapsTime_accumulator = 0.f;
	}
};*/