#pragma once

#include "Lista/lista.h"
#include "../Entes/Entity/entity.h"

class EntitiesLista
{
public:
	EntitiesLista();
	~EntitiesLista();

	unsigned int GetSize() { return this->entities.GetSize(); };

	void AddEntity(Entity* entity);
	void AddRange(std::list<Entity*>* _entities);
	void RemoveEntity(const unsigned long long int entityId);
	void RemoveRange(const std::vector<unsigned long long int> entityId);

	Entity* operator[](const unsigned int& val)
	{
		return this->entities[val].GetInfo();
	}
private:
	Lista<Entity*> entities;
};