#pragma once

#include "../Entities/Player/player.h"
#include "../Managers/Graphic Manager/graphic_manager.h"
#include "../ListConteiner/lista.h"
#include "../Entities/Camera/camera.h"

class Game
{
public:
	Game();
	~Game();

	bool StartGame();

private:
	std::list<Characters::Player> players;
	sf::RenderWindow window;

	Camera camera;
	GraphicManager graphicManager;
};