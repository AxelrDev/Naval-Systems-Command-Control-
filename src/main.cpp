#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Inicializa la semilla para los números aleatorios
    std::srand(static_cast<unsigned int>(std::time(0)));

    int rows = 10;
    int cols = 10;
    int numShips = 5;  // Número de barcos para cada jugador
    Game game(rows, cols, numShips);
    game.play();

    return 0;
}
