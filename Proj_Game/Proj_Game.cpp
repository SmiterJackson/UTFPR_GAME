#include "stdafx.h"
#include "game/game.h"

int main()
{
    Game* game = Game::GetInstance();
    if (game == nullptr)
        return -1;

    setlocale(LC_ALL, "");

    if (!game->StartGame())
        std::cout << "Não foi possível abrir a janela de contexto." << std::endl;

    Game::DesconstructInstance();
    return 0;
}