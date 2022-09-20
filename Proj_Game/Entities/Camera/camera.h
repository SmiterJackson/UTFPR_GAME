#pragma once

#include "../Player/player.h"

class Camera
{
public:
	Camera(std::list<Characters::Player>* _players = nullptr);
	Camera(const sf::Vector2f _center, const sf::Vector2f _size, std::list<Characters::Player>* _players = nullptr, const sf::FloatRect* _mapBounds = nullptr);
	~Camera();

	void Execute();
	const sf::FloatRect CameraBounds();
	std::vector<Entity*> GetCameraEntities(std::vector<Entity*>* entities);

	void SetMapBounds(const sf::FloatRect* _mapBounds)
	{
		if (_mapBounds == nullptr)
			return;
		this->mapBounds = *_mapBounds;
	};
	sf::View* GetView() { return &this->view; }

private:
	std::list<Characters::Player>* players;

	sf::FloatRect mapBounds;
	sf::View view;
};