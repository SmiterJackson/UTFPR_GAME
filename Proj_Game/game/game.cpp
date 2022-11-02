#include "game.h"
using namespace Manager;

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define GRID_SIZE 32.f

#define ZOOM_COEFF 2.0f

#define IMAGE_COEFFICIENT 2.5f

#define BOUNDS sf::FloatRect((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT))

unsigned short int Game::gameState = Trait::GameStateType::IN_GAME;

Game::Game():
    graphicManager(nullptr),
    mouse(GRID_SIZE),
    interfaces(),
    elapsedTime(0.f)
{
    graphicManager = GraphicManager::GetGraphicInstance(elapsedTime, &this->interfaces);
    this->mouse.SetWindowReference(&this->graphicManager->GetWindow());

    std::vector<std::string> paths(
    {
        "Proj_Game/Resources/parallax_background/foreground.png",
        "Proj_Game/Resources/parallax_background/back-buildings.png",
        "Proj_Game/Resources/parallax_background/far-buildings.png"
    });

    Stage* stage = new Stage(BOUNDS, "", paths, IMAGE_COEFFICIENT);
    interfaces.push(static_cast<GUI::Interface*>(stage));
};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!GraphicManager::IsWindowOpen())
        return false;

    sf::Clock clock;
    while (GraphicManager::IsWindowOpen())
    {
        this->elapsedTime = clock.restart().asSeconds();
        this->mouse.Execute(this->elapsedTime);

        this->UpdateGameState();

        sf::Event event;
        while (GraphicManager::GetWindow().pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                GraphicManager::DesconstructGraphicInstance();
                this->graphicManager = nullptr;
                break;
            case sf::Event::Resized:
                this->graphicManager->WindowResize();
                break;
            default:
                this->interfaces.top()->InputHandle(event);
                break;
            }
        }

        this->interfaces.top()->Execute(this->elapsedTime);

        if(this->graphicManager != nullptr)
            this->graphicManager->Draw();
    }

    return true;
}

void Game::UpdateGameState()
{
    GUI::Interface* currentInter = this->interfaces.top();
    GUI::Interface* newInterface = nullptr;

    switch (this->gameState)
    {
    case Trait::GameStateType::PAUSE_MENU:
        if (currentInter->GetType() == Trait::GameStateType::IN_GAME)
            newInterface = static_cast<GUI::Interface*>(new GUI::PauseInterface(&this->mouse, static_cast<Stage*>(currentInter)));
        break;
    case Trait::GameStateType::IN_GAME:
        if (currentInter->GetType() == Trait::GameStateType::PAUSE_MENU)
            this->interfaces.pop();
        break;
    default:
        break;
    }

    if (newInterface != nullptr)
        this->interfaces.emplace(newInterface);
};