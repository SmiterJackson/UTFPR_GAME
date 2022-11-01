#pragma once

#include "../../Managers/ColisionManager/colisionManager.h"
#include "../GUI/Interfaces/Interface/interface.h"
#include "../Entes/Obstacles/obstacle/obstacle.h"
#include "../Characters/Player/player.h"
#include "Parallax/parallax.h"

class Stage : public GUI::Interface
{
public:
	class Parallax;

public:
	Stage();
	Stage(unsigned short int* pGameState, const sf::RectangleShape& _hitBox, const std::string& stagePath,
		  const std::vector<std::string>& BackgroundPaths, const float size_coefficient);
	~Stage();

	const sf::FloatRect GetBounds() const { return this->worldBounds; };

	void Initalize(const float size_coefficient);
	void InputHandle(const sf::Event& _event);

	void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
	void Execute(const float& pElapsedTime);
	void ReadArchive(const std::string path);

	void AddEntity(Entity* entity);
	void AddRange(std::list<Entity*>* _entities);
	void RemoveEntity(const unsigned long long int entityId);
	void RemoveRange(const std::vector<unsigned long long int> entityId);

	void AddPlayer();
	void RemovePlayer();

protected:
	sf::FloatRect worldBounds;

	Manager::ColisionManager colision_manager;
	Parallax background;

	Lista<Entity*> entities;

	unsigned short int* pGameState;
};