#include "stdafx.h"
#include "game/game.h"

int main()
{
    Game game;
    setlocale(LC_ALL, "");

    if (!game.StartGame())
        std::cout << "N�o foi poss�vel abrir a janela de contexto." << std::endl;

    return 0;
}