#pragma once

#include "../Entes/Entity/entity.h"
#include "../List/Lista/lista.h"

namespace GUI
{
	class Stage;
}

namespace Manager
{
	typedef std::list<Entity*> Entities;

	class ColisionManager
	{
	public:
		static ColisionManager* GetInstance(Lista<Entity*>* _pEntities = nullptr);
		static void DeconstructInstance();

		void UpdateColisions(const float& pElapsedTime);

		void Add(Entity* entity);
		void AddRange(Lista<Entity*>* _entities);
		void Remove(const unsigned long long int entityId);
		void RemoveRange(const std::vector<unsigned long long int> entitiesIds);

	private:
		ColisionManager(Lista<Entity*>* _pEntities = nullptr);
		~ColisionManager();

		void CheckInColision(Entity* entity, Entity* other);
		void CheckOfColision(Entity* entity);

	private:
		static ColisionManager* instance;

		Entities entities;
		Entities staticEntities;
		float accumulator;
	};
}