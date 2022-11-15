#pragma once

#include "Lista/lista.h"
#include "../Entes/Entity/entity.h"

class EntitiesLista
{
public:
	EntitiesLista();
	~EntitiesLista();

	void AddEntity(Entity* entity);
	void AddRange(std::list<Entity*>* _entities);
	void RemoveEntity(const unsigned long long int entityId);
	void RemoveRange(const std::vector<unsigned long long int> entityId);

private:
	Lista<Entity*> entities;
};