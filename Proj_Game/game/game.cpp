#include "game.h"

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define GRID_SIZE 32.f

#define ZOOM_COEFF 2.0f

#define IMAGE_COEFFICIENT 2.5f

#define BOUNDS sf::Vector2f((352.f * IMAGE_COEFFICIENT * 4.f), (172.f * IMAGE_COEFFICIENT))

Game::Game():
    window(sf::VideoMode(WINDOW_SIZE_X_I, WINDOW_SIZE_Y_I), "JANELA DE CONTEXTO - GRÁFICO"),
    graphicManager(Manager::GraphicManager::GetGraphManagerInstance()),
    camera(
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(WINDOW_SIZE_X_F / ZOOM_COEFF, WINDOW_SIZE_Y_F / ZOOM_COEFF),
        ZOOM_COEFF, nullptr, true, true, true, true
    ),
    mouse(GRID_SIZE, &this->window),
    interfaces(),
    elapsedTime(0.f),
    gameState(GameStateType::IN_GAME)
{
    std::vector<std::string> paths(
    {
        "Proj_Game/Resources/parallax_background/foreground.png",
        "Proj_Game/Resources/parallax_background/back-buildings.png",
        "Proj_Game/Resources/parallax_background/far-buildings.png"
    });
    Stage* stage = new Stage(
        &this->gameState, &this->camera, sf::RectangleShape(BOUNDS), "",
        paths, IMAGE_COEFFICIENT
    );
    GUI::PauseInterface* pauseInter = new GUI::PauseInterface(
        &this->gameState, &this->camera, &this->mouse, stage
    );

    this->window.setKeyRepeatEnabled(false);
    this->graphicManager->SetWindowReference(&this->window);
    this->graphicManager->SetGameStateReference(&this->gameState);
    this->graphicManager->SetInterfacesReference(&this->interfaces);

    interfaces.emplace(
        std::pair<unsigned short int, GUI::Interface*>(
            stage->GetType(), static_cast<GUI::Interface*>(stage)
        )
    );
    interfaces.emplace(
        std::pair<unsigned short int, GUI::Interface*>(
            pauseInter->GetType(), static_cast<GUI::Interface*>(pauseInter)
        )
    );
};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!window.isOpen())
        return false;

    sf::Clock clock;
    while (window.isOpen())
    {
        this->elapsedTime = clock.restart().asSeconds();

        this->mouse.Execute(this->elapsedTime);

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                this->camera.WindowResized(this->window);
                break;
            default:
                this->interfaces[this->gameState]->InputHandle(event);
                break;
            }
        }

        this->interfaces[this->gameState]->Execute(this->elapsedTime);

        this->graphicManager->Draw(this->elapsedTime);

        window.setView((*this->camera.GetView()));
        window.display();
    }

    return true;
}