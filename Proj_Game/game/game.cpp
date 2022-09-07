#include "game.h"

#include "../Entities/Parallax/parallax.h"
#include "../Entities/Camera/camera.h"

#define RECT_SIZE 50.f
#define VELOCITY 0.175f

#define WINDOW_SIZE_X_F 1440.f
#define WINDOW_SIZE_X_I 1440
#define WINDOW_SIZE_Y_F 810.f
#define WINDOW_SIZE_Y_I 810

#define IMAGE_COEFFICIENT 2.5f

Game::Game():
    players(),
    window(sf::VideoMode(WINDOW_SIZE_X_I, WINDOW_SIZE_Y_I), "JANELA DE CONTEXTO - GRÁFICO"), 
    graphicManager(&window)
{};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!window.isOpen())
        return false;

    sf::Vector2f position(0.f, (192 * IMAGE_COEFFICIENT) - RECT_SIZE - 36.f);
    float X_Coeff = 4.f, Y_Coeff = X_Coeff / 2.f;

    sf::FloatRect bounds((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT));

    this->players.emplace_back();
    players.front().MovePosition(position);
    this->players.emplace_back();
    players.back().MovePosition(position + sf::Vector2f(48.f, 0.f));

    Camera camera(sf::Vector2f(WINDOW_SIZE_X_F / X_Coeff, WINDOW_SIZE_Y_F / X_Coeff), sf::Vector2f(WINDOW_SIZE_X_F / Y_Coeff, WINDOW_SIZE_Y_F / Y_Coeff), &this->players, &bounds);

    std::vector<std::string> paths(
    {   "Resources/parallax_background/foreground.png",
        "Resources/parallax_background/back-buildings.png",
        "Resources/parallax_background/far-buildings.png" 
    });
    ParallaxBackground bckg(camera.GetView(), paths, 2.5f);

    float timediff = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        timediff = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                players.front().PlayerInputHandler(event);
                if(players.size() > 1)
                    players.back().PlayerInputHandler(event);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                players.front().PlayerInputHandler(event);
                if (players.size() > 1)
                    players.back().PlayerInputHandler(event);
            }
        }

        players.front().Execute(timediff);
        if (players.size() > 1)
            players.back().Execute(timediff);

        bckg.Execute(timediff);
        camera.Execute(timediff);

        window.clear();

        bckg.SelfPrint(this->window, timediff);

        players.front().SelfPrint(this->window, timediff);
        if (players.size() > 1)
            players.back().SelfPrint(this->window, timediff);

        window.setView(*camera.GetView());
        window.display();
    }

    return true;
}