#pragma once

#include "../Entities/Characters/Player/player.h"
#include "../Managers/Graphic Manager/graphic_manager.h"
#include "../ListConteiner/lista.h"
#include "../Entities/Camera/camera.h"
#include "../Entities/Obstacles/obstacle/obstacle.h" 
#include "../Managers/Colision Manager/colisionManager.h"
#include "../Entities/StageClass/stage.h"
#include "../GUI/Interfaces/PauseInterface/pauseInterface.h"
#include "../Entities/Mouse/mouse.h"

class Game
{
public:
	Game();
	~Game();

	bool StartGame();

	enum STATE { MAIN_MENU = 0, PLAYING, PAUSED };

private:
	sf::RenderWindow window;

	Camera camera;
	Mouse mouse;
	GraphicManager graphicManager;

	std::vector<Ente*> stateEnte;

	float elapsedTime;
	short int gameState;
};