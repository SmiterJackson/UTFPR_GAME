#pragma once

#include "../Managers/GraphicManager/graphic_manager.h"
#include "../GUI/Interfaces/PauseInterface/pauseInterface.h"
#include "../Entes/Stage/stage.h"

typedef std::unordered_map<unsigned short int, GUI::Interface*> InterfaceMap;

class Game
{
public:
	Game();
	~Game();

	bool StartGame();

private:
	sf::RenderWindow window;

	Manager::GraphicManager* graphicManager;
	Camera camera;
	Mouse mouse;

	InterfaceMap interfaces;

	float elapsedTime;
	unsigned short int gameState;
};