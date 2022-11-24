#include "entitiesLista.h"

EntitiesLista::EntitiesLista()
{};
EntitiesLista::~EntitiesLista()
{
	Lista<Entity*>::Iterador it;

	for (it = this->entities.begin(); it != this->entities.end(); it++)
	{
		delete (*it);
		this->entities.PopAt(it);
		break;
	}
};

void EntitiesLista::AddEntity(Entity* entity)
{
	if (entity == nullptr)
		return;

	this->entities.PushBack(entity);
};
void EntitiesLista::AddRange(std::list<Entity*>* _entities)
{
	std::list<Entity*>::iterator it;

	if (_entities == nullptr)
		return;

	for (it = _entities->begin(); it != _entities->end(); it++)
		this->entities.PushBack(*it);
};
void EntitiesLista::RemoveEntity(const unsigned long long int entityId)
{
	Lista<Entity*>::Iterador it;

	for (it = this->entities.begin(); it != this->entities.end(); it++)
	{
		if ((*it)->GetId() == entityId)
		{
			delete (*it);
			this->entities.PopAt(it);
			break;
		}
	}
};
void EntitiesLista::RemoveRange(const std::vector<unsigned long long int> entityId)
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
		}
	}
};