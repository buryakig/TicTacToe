#include <SFML/Graphics.hpp>
#include "Game.h"
#include "CoreDefines.h"

int main()
{
    Blink::Game TicTacToe(SCREEN_WIDTH, SCREEN_HEIGHT, "SFML Starter");

    TicTacToe.Prepare();
    TicTacToe.Run();
    
    return EXIT_SUCCESS;
}