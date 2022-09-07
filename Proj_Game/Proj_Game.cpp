#include "stdafx.h"
#include "game/game.h"

int main()
{
    Game game;
    setlocale(LC_ALL, "");

    if (!game.StartGame())
        std::cout << "Não foi possível abrir a janela de contexto." << std::endl;

    return 0;
}