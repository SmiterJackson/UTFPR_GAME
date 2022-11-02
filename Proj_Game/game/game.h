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

	static const unsigned short int GetGameState() { return gameState; };
	static void SetGameState(const unsigned short int _gameState) { gameState = _gameState; };

	bool StartGame();

private:
	void UpdateGameState();

private:
	static unsigned short int gameState;

	Manager::GraphicManager* graphicManager;
	Mouse mouse;

	Interfaces interfaces;

	float elapsedTime;
};