#include "game.h"

#include "../Entities/Parallax/parallax.h"
#include "../Entities/Camera/camera.h"

#define FONT "Proj_Game/Resources/fonts/EquipmentPro.ttf"

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define GRID_SIZE 32.f

#define ZOOM_COEFF 2.0f

#define IMAGE_COEFFICIENT 2.5f

#define BOUNDS sf::FloatRect((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT))

Game::Game():
    window(sf::VideoMode(WINDOW_SIZE_X_I, WINDOW_SIZE_Y_I), "JANELA DE CONTEXTO - GRÁFICO"),
    camera(
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(WINDOW_SIZE_X_F / ZOOM_COEFF, WINDOW_SIZE_Y_F / ZOOM_COEFF),
        ZOOM_COEFF, nullptr, nullptr, true, true, true, true),
    mouse(GRID_SIZE, &this->window),
    graphicManager(&window),
    stateEnte(),
    elapsedTime(0.f),
    gameState(STATE::MAIN_MENU)
{
    this->window.setKeyRepeatEnabled(false);
};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!window.isOpen())
        return false;

    sf::FloatRect bounds((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT));
    std::vector<std::string> paths(
    {   "Proj_Game/Resources/parallax_background/foreground.png",
        "Proj_Game/Resources/parallax_background/back-buildings.png",
        "Proj_Game/Resources/parallax_background/far-buildings.png"
    });

    //Stage stage(&this->gameState , &this->camera, &this->elapsedTime, bounds, std::string(), paths, IMAGE_COEFFICIENT);
    //this->camera.SetMapBounds(&stage.GetMapBounds());
    this->stateEnte.emplace_back(static_cast<Ente*>(
            new Stage(&this->gameState, &this->camera, &this->elapsedTime, bounds, std::string(), paths, IMAGE_COEFFICIENT)
        )
    );
    this->camera.SetMapBounds(&static_cast<Stage*>(this->stateEnte.back())->GetMapBounds());

    sf::Clock clock;
    
    while (window.isOpen())
    {
        this->elapsedTime = clock.restart().asSeconds();

        if (this->stateEnte.size() <= 1 && this->gameState == Game::PAUSED)
            this->stateEnte.emplace_back(static_cast<Ente*>(
                    new GUI::PauseInterface(&this->elapsedTime, &this->gameState, &this->camera, &this->mouse,
                        static_cast<Stage*>(this->stateEnte.back()), &this->stateEnte, FONT
                    )
                )
            );
        else if (this->stateEnte.size() == 2 && this->gameState == Game::PLAYING)
        {
            delete this->stateEnte.top();
            this->stateEnte.pop();
        }

        this->mouse.Execute();

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
            //case sf::Event::KeyPressed:
            //    stage.InputHandle(event);
            //    break;
            //case sf::Event::KeyReleased:
            //    stage.InputHandle(event);
            //    break;
            default:
                this->stateEnte.top()->InputHandle(event);
                break;
            }
        }

        //stage.Execute();
        this->stateEnte.top()->Execute();
        this->camera.Execute();

        window.clear();

        //stage.SelfPrint(this->window);
        this->stateEnte.top()->SelfPrint(this->window);

        window.setView((*this->camera.GetView()));
        window.display();
    }

    return true;
}