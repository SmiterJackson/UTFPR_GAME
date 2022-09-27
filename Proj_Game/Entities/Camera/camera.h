#pragma once

#include "../Player/player.h"
#include "../../ListConteiner/lista.h"

class Camera : public Ente
{
public:
	Camera();
	Camera(const sf::Vector2f _center, const sf::Vector2f _size, std::list<Characters::Player>* _pEntities = nullptr, sf::FloatRect* _mapBounds = nullptr);
	~Camera();

	void Execute();
	const sf::FloatRect CameraBounds();
	std::vector<Entity*> GetCameraEntities(std::vector<Entity*>* entities);

	void SetMapBounds(sf::FloatRect* _mapBounds) { this->mapBounds = _mapBounds; };
	sf::View* GetView() { return &this->view; }

	void AddPlayer(Characters::Player* pPlayer);
	void AddPlayerRange(std::list<Characters::Player*>* pPlayerList);
	void RemovePlayer(unsigned long long int id);

private:
	std::list<Characters::Player*> players;

	sf::FloatRect* mapBounds;
	sf::View view;
};