#pragma once

#include "../Managers/GraphicManager/graphic_manager.h"
#include "../GUI/Interfaces/PauseInterface/pauseInterface.h"
#include "../Entes/Stage/stage.h"

typedef std::stack<GUI::Interface*> Interfaces;

class Game
{
public:
	Game();
	~Game();

	bool StartGame();

private:
	void UpdateGameState();

private:
	Manager::GraphicManager* graphicManager;
	Mouse mouse;

	Interfaces interfaces;

	float elapsedTime;
	unsigned short int gameState;
};