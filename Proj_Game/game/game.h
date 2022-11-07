#pragma once

#include "../Managers/EventManager/event_manager.h"
#include "../Managers/GraphicManager/graphic_manager.h"
#include "../GUI/Interfaces/PauseInterface/pauseInterface.h"
#include "../Entes/Stage/stage.h"

typedef std::stack<GUI::Interface*> Interfaces;

const enum GameStateType
{
	MAIN_MENU = 0,
	IN_GAME,
	PAUSE_MENU,
	SUB_MENU
};

class Game
{
public:
	static Game* GetInstance();
	static void DesconstructInstance();

	static const unsigned short int GetGameState() { return gameState; };
	static void SetGameState(const unsigned short int _gameState) 
	{ 
		gameState = _gameState;
		UpdateGameState();
	};

	static float& GetElapsedTime() { return elapsedTime; };

	bool StartGame();

private:
	Game();
	~Game();

	static void UpdateGameState();

private:
	static Game* game;
	static Interfaces interfaces;
	static unsigned short int gameState;
	static float elapsedTime;

	Manager::GraphicManager* graphicManager;
	Manager::EventManager* eventManager;
};