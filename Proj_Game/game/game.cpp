#include "game.h"
using namespace Manager;
using namespace GUI;

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define ZOOM_COEFF 2.0f

Game*               Game::game          = nullptr;
Interfaces          Game::interfaces    = Interfaces();
unsigned short int  Game::gameState     = GameStateType::IN_GAME;
float               Game::elapsedTime   = float(0.f);

Game* Game::GetInstance()
{
    if (game == nullptr)
    {
        game = new Game();
        if (game == nullptr)
            std::cerr << "Nao foi possivel instanciar o jogo: game." << std::endl;
    }

    return game;
};
void Game::DesconstructInstance()
{
    if (game == nullptr)
        delete game;
};

Game::Game():
    graphicManager(GraphicManager::GetInstance(&interfaces)),
    eventManager(EventManager::GetInstance())
{
    Stages::Stage1* stage = new Stages::Stage1();
    interfaces.push(static_cast<GUI::Interface*>(stage));
};
Game::~Game()
{
    GraphicManager::DesconstructInstance();
    EventManager::DeconstructInstance();
};

bool Game::StartGame()
{
    if (!GraphicManager::IsWindowOpen())
        return false;

    sf::Clock clock;
    while (GraphicManager::IsWindowOpen())
    {
        this->elapsedTime = clock.restart().asSeconds();

        this->interfaces.top()->Execute();

        this->graphicManager->Update();
        this->eventManager->Update();
    }

    return true;
}

void Game::UpdateGameState()
{
    GUI::Interface* currentInter = interfaces.top();
    GUI::Interface* newInterface = nullptr;

    switch (gameState)
    {
    case GameStateType::PAUSE_MENU:
        if (currentInter->GetType() == GameStateType::IN_GAME)
            newInterface = static_cast<Interface*>(new PauseInterface(static_cast<Stage*>(currentInter)));
        break;
    case GameStateType::IN_GAME:
        if (currentInter->GetType() == GameStateType::PAUSE_MENU)
            interfaces.pop();
        break;
    default:
        break;
    }

    if (newInterface != nullptr)
        interfaces.emplace(newInterface);
};