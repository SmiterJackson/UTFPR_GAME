#pragma once

#include "../../Entities/Entity/entity.h"
#include "../../Entities/Camera/camera.h"

class ColisionManager
{
public:
	ColisionManager();
	ColisionManager(Camera* pCamera, const sf::FloatRect _mapBorders, float* _pElapsedTime, std::list<Entity*>* _entities = nullptr);
	ColisionManager(Camera* pCamera, const sf::FloatRect _mapBorders, float* _pElapsedTime, std::vector<Entity*>* _entities = nullptr);
	~ColisionManager();
	
	void UpdateColisions();
	void CheckColision(Entity* entity, Entity* other);
	void CheckOutOfCamera(Entity* entity);

	void AddEntity(Entity* entity);
	void AddRange(std::list<Entity*>* _entities);
	void AddRange(std::vector<Entity*>* _entities);
	void RemoveEntity(const unsigned int entityId);

	void SortElements();

private:
	void QuickSortRecursion(unsigned int start, unsigned int end);
	unsigned int SortPartition(unsigned int start, unsigned int end);
	unsigned int Mediana(unsigned int val_1, unsigned int val_2, unsigned int val_3);
	void ExchangePointers(Entity** p1, Entity** p2);

private:
	std::vector<Entity*> entities;
	sf::FloatRect mapBorders;

	Camera* cameraRef;

	float elaps_accumul;
	float* pElapsedTime;
};