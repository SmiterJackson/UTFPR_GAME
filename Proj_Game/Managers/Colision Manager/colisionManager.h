#pragma once

#include "../../Entities/Camera/camera.h"

class Stage;

class ColisionManager
{
public:
	ColisionManager();
	ColisionManager(Stage* pStage, Camera* pCamera, float* _pElapsedTime, Lista<Ente*>* _pEntities = nullptr);
	~ColisionManager();
	
	void UpdateColisions();
	void CheckColision(Entity* entity, Entity* other);
	void CheckOutOfCamera(Entity* entity);
	void CheckOutOfMap(Entity* entity);

	void Add(Entity* entity);
	void AddRange(Lista<Ente*>* _entities);
	void AddRange(std::vector<Entity*>* _entities);
	void Remove(const unsigned int entityId);
	void RemoveRange(const std::vector<unsigned int> entitiesIds);

	void SortElements();

private:
	void QuickSortRecursion(unsigned int start, unsigned int end);
	unsigned int SortPartition(unsigned int start, unsigned int end);
	unsigned int Mediana(unsigned int val_1, unsigned int val_2, unsigned int val_3);
	void ExchangePointers(Entity** p1, Entity** p2);

private:
	std::vector<Entity*> entities;

	Stage* stageRef;
	Camera* cameraRef;

	float elaps_accumul;
	float* pElapsedTime;
};