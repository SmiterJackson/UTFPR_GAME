#pragma once

#include "../Entities/Player/player.h"
#include "../Managers/Graphic Manager/graphic_manager.h"
#include "../ListConteiner/lista.h"
#include "../Entities/Camera/camera.h"
#include "../Entities/Obstacles/obstacle/obstacle.h" 
#include "../Managers/Colision Manager/colisionManager.h"
#include "../Entities/StageClass/stage.h"

class Game
{
public:
	Game();
	~Game();

	bool StartGame();

private:
	sf::RenderWindow window;

	Camera camera;
	GraphicManager graphicManager;

	float elapsedTime;
};