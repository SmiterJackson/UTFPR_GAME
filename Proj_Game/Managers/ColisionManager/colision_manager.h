#pragma once

#include "../Entes/Entity/entity.h"
#include "../ListConteiner/lista.h"

class Stage;

namespace Manager
{
	typedef std::vector<Entity*> ColisonVector;

	class ColisionManager
	{
	public:
		static ColisionManager* GetInstance(Stage& stage, Lista<Entity*>* _pEntities = nullptr);
		static void DeconstructInstance();

		void UpdateColisions(const float& pElapsedTime);

		void Add(Entity* entity);
		void AddRange(Lista<Entity*>* _entities);
		void Remove(const unsigned long long int entityId);
		void RemoveRange(const std::vector<unsigned long long int> entitiesIds);

		void SortElements();

	private:
		ColisionManager(Stage& stage, Lista<Entity*>* _pEntities = nullptr);
		~ColisionManager();

		void CheckInColision(Entity* entity, Entity* other);
		void CheckOfColision(Entity* entity);

		void QuickSortRecursion(unsigned int start, unsigned int end);
		unsigned int SortPartition(unsigned int start, unsigned int end);
		unsigned int Mediana(unsigned int val_1, unsigned int val_2, unsigned int val_3);
		void ExchangePointers(Entity** p1, Entity** p2);

	private:
		static ColisionManager* colisionManagerInstance;

		ColisonVector entities;
		Stage& stageRef;

		float accumulator;
	};
}