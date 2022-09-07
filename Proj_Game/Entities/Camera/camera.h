#pragma once

#include "../Player/player.h"

class Camera : public Ente
{
public:
	Camera(std::list<Characters::Player>* _players = nullptr);
	Camera(const sf::Vector2f _center, const sf::Vector2f _size, std::list<Characters::Player>* _players = nullptr, const sf::FloatRect* _mapBounds = nullptr);
	~Camera();

	void Execute(const float elapsedTime);
	void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime);
	const sf::FloatRect CameraBounds();

	void SetMapBounds(const sf::FloatRect* _mapBounds)
	{
		if (_mapBounds == nullptr)
			return;
		this->mapBounds = *_mapBounds;
	};
	sf::View* GetView() { return &this->view; }

private:
	sf::View view;
	std::list<Characters::Player>* players;

	sf::FloatRect mapBounds;
};