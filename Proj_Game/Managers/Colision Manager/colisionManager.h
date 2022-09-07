#pragma once

#include "../../Entities/Entity/entity.h"
#include "../../Entities/Camera/camera.h"

class ColisionManager
{
public:
	ColisionManager();
	ColisionManager(const sf::FloatRect _mapBorders, const std::list<Entity*>& _entities = std::list<Entity*>());
	~ColisionManager();

	void AddEntity(const Entity* entity);
	void RemoveEntity(const unsigned int entityId);
	void CheckColisions(const float elapsedTime);

private:
	//std::list</*Obstacle*/> obstacles;
	//std::vector</*Enemies*/> enemies;
	sf::FloatRect mapBorders;
	sf::View viewRef;

	Camera* cameraRef;
	float elapsTime_accumulator;
};