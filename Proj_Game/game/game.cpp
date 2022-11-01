#include "game.h"
using namespace Manager;

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define GRID_SIZE 32.f

#define ZOOM_COEFF 2.0f

#define IMAGE_COEFFICIENT 2.5f

#define BOUNDS sf::FloatRect((352.f * IMAGE_COEFFICIENT * -2.f), (172.f * IMAGE_COEFFICIENT), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT))

Game::Game():
    graphicManager(nullptr),
    mouse(GRID_SIZE),
    interfaces(),
    elapsedTime(0.f),
    gameState(Trait::GameStateType::IN_GAME)
{
    graphicManager = GraphicManager::GetGraphicInstance(elapsedTime, &this->interfaces);
    this->mouse.SetWindowReference(&this->graphicManager->GetWindow());

    std::vector<std::string> paths(
    {
        "Proj_Game/Resources/parallax_background/foreground.png",
        "Proj_Game/Resources/parallax_background/back-buildings.png",
        "Proj_Game/Resources/parallax_background/far-buildings.png"
    });

    Stage* stage = new Stage(
        &this->gameState, BOUNDS, "",
        paths, IMAGE_COEFFICIENT
    );
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
        this->graphicManager->Draw();
    }

    return true;
}

void Game::UpdateGameState()
{
    switch (this->gameState)
    {
    case Trait::GameStateType::PAUSE_MENU:
        if(this->interfaces.top()->GetType() == Trait::GameStateType::IN_GAME)
        interfaces.emplace(static_cast<GUI::Interface*>(
            new GUI::PauseInterface(
                &this->gameState, &this->mouse, static_cast<Stage*>(this->interfaces.top()))
            )
        );
        break;
    default:
        break;
    }
};