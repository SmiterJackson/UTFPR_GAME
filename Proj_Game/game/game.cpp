#include "game.h"

#include "../Entities/Parallax/parallax.h"
#include "../Entities/Camera/camera.h"
#define VELOCITY 0.175f

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define X_COEFF 3.5f
#define Y_COEFF (X_COEFF / 2.f)

#define IMAGE_COEFFICIENT 2.5f

#define BOUNDS sf::FloatRect((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT))

Game::Game():
    window(sf::VideoMode(WINDOW_SIZE_X_I, WINDOW_SIZE_Y_I), "JANELA DE CONTEXTO - GRÁFICO"),
    camera(
        sf::Vector2f(WINDOW_SIZE_X_F / X_COEFF, WINDOW_SIZE_Y_F / X_COEFF),
        sf::Vector2f(WINDOW_SIZE_X_F / Y_COEFF, WINDOW_SIZE_Y_F / Y_COEFF),
        nullptr, nullptr),
    graphicManager(&window),
    elapsedTime(0.f)
{};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!window.isOpen())
        return false;

    sf::FloatRect bounds((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT));

    //Camera camera(sf::Vector2f(WINDOW_SIZE_X_F / X_COEFF, WINDOW_SIZE_Y_F / X_COEFF),
    //    sf::Vector2f(WINDOW_SIZE_X_F / Y_COEFF, WINDOW_SIZE_Y_F / Y_COEFF),
    //    nullptr, &bounds);
    std::vector<std::string> paths(
    {   "Resources/parallax_background/foreground.png",
        "Resources/parallax_background/back-buildings.png",
        "Resources/parallax_background/far-buildings.png" 
    });

    Stage stage(&camera, &this->elapsedTime, bounds, std::string(), paths, IMAGE_COEFFICIENT);
    this->camera.SetMapBounds(&stage.GetMapBounds());

    sf::Clock clock;
    
    while (window.isOpen())
    {
        this->elapsedTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                stage.InputHandle(event);
            if (event.type == sf::Event::KeyReleased)
                stage.InputHandle(event);
        }

        stage.Execute();
        this->camera.Execute();

        window.clear();

        stage.SelfPrint(this->window);

        window.setView((*this->camera.GetView()));
        window.display();
    }

    return true;
}