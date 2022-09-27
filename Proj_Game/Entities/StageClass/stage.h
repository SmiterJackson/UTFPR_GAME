#pragma once

#include "../../Managers/Colision Manager/colisionManager.h"
#include "../../Entities/Parallax/parallax.h"
#include "../../ListConteiner/lista.h"
#include "../Obstacles/obstacle/obstacle.h"

class Player;

class Stage : public Ente
{
public:
	Stage();
	Stage(Camera* camera, float* pElapsedTime, sf::FloatRect _mapBounds, const std::string& stagePath, 
		  const std::vector<std::string>& BackgroundPaths, const float size_coefficient);
	~Stage();

	virtual void Execute();
	virtual void SelfPrint(sf::RenderWindow& context_window);
	virtual void ReadArchive(const std::string path);

	void Initalize(const float size_coefficient);
	void InputHandle(const sf::Event _event);

	void AddEntity(Ente* entity);
	void AddRange(std::list<Ente*>* _entities);
	void AddRange(std::vector<Ente*>* _entities);
	void RemoveEntity(const unsigned int entityId);

	sf::FloatRect& GetMapBounds() { return this->mapBounds; };
	void SetMapBounds(const sf::FloatRect _mapBounds) { this->mapBounds = _mapBounds; };

	ColisionManager* GetCollisionManager() { return &this->colision_manager; };
	ParallaxBackground* GetParallax() { return &this->background; };

protected:
	sf::FloatRect mapBounds;

	ColisionManager colision_manager;
	ParallaxBackground background;

	Camera* pCamera;
	Lista<Ente*> entities;
};