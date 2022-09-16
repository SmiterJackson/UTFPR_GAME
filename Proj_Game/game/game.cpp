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

#define OBSTACLE_TEXTURE_REF "Resources/tile_sets/Texture/TX_Tileset_Ground.png"
#define OBSTACLE_SIZE 32

Game::Game():
    players(),
    window(sf::VideoMode(WINDOW_SIZE_X_I, WINDOW_SIZE_Y_I), "JANELA DE CONTEXTO - GRÁFICO"), 
    graphicManager(&window),
    elapsedTime(0.f)
{};
Game::~Game()
{};

bool Game::StartGame()
{
    if (!window.isOpen())
        return false;

    sf::Vector2f position(0.f, (192 * IMAGE_COEFFICIENT) - RECT_SIZE - 36.f);
    float X_Coeff = 3.5f, Y_Coeff = X_Coeff / 2.f;

    sf::FloatRect bounds((352.f * IMAGE_COEFFICIENT * -2.f), (-192.f + 40.f), (352.f * IMAGE_COEFFICIENT * 2.f), (192.f * IMAGE_COEFFICIENT));

    this->players.emplace_back(&this->elapsedTime);
    players.front().MovePosition(position);
    //this->players.emplace_back(&this->elapsedTime);
    //players.back().MovePosition(position + sf::Vector2f(48.f, 0.f));
    std::list<Characters::Player>::iterator it;

    Camera camera(sf::Vector2f(WINDOW_SIZE_X_F / X_Coeff, WINDOW_SIZE_Y_F / X_Coeff), sf::Vector2f(WINDOW_SIZE_X_F / Y_Coeff, WINDOW_SIZE_Y_F / Y_Coeff), &this->players, &bounds);

    std::vector<std::string> paths(
    {   "Resources/parallax_background/foreground.png",
        "Resources/parallax_background/back-buildings.png",
        "Resources/parallax_background/far-buildings.png" 
    });
    ParallaxBackground bckg(camera.GetView(), &this->elapsedTime, paths, 2.5f);

    std::vector<Obstacles::Obstacle> obstacles;
    obstacles.reserve(size_t(5));
    for (int f = 1; f < 6; f++)
    {
        obstacles.emplace_back(sf::RectangleShape(sf::Vector2f(OBSTACLE_SIZE, OBSTACLE_SIZE)), &this->elapsedTime, 
            OBSTACLE_TEXTURE_REF, sf::IntRect(0, 0, OBSTACLE_SIZE, OBSTACLE_SIZE)
        );
        obstacles.back().MovePosition(sf::Vector2f(position.x + (OBSTACLE_SIZE * f), position.y));
    }
    std::vector<Obstacles::Obstacle>::iterator itobs;

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
            {
                for (it = this->players.begin(); it != this->players.end(); it++)
                    it->PlayerInputHandler(event);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                for (it = this->players.begin(); it != this->players.end(); it++)
                    it->PlayerInputHandler(event);
            }
        }

        for (it = this->players.begin(); it != this->players.end(); it++)
            it->Execute();

        bckg.Execute();
        camera.Execute();

        window.clear();

        bckg.SelfPrint(this->window);

        for (itobs = obstacles.begin(); itobs != obstacles.end(); itobs++)
            itobs->SelfPrint(this->window);

        for (it = this->players.begin(); it != this->players.end(); it++)
            it->SelfPrint(this->window);

        window.setView(*camera.GetView());
        window.display();
    }

    return true;
}