#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
public:
    // Constructor: crea el juego con un tablero de rows x cols y numShips barcos.
    Game(int rows, int cols, int numShips);
    // Destructor: libera la memoria de los jugadores.
    ~Game();

    // Ejecuta el bucle principal del juego.
    void play();

private:
    Player* player;
    Player* computer;
    int rows;
    int cols;
    int numShips;

    // Procesa el turno del jugador.
    void playerTurn();
    // Procesa el turno de la computadora.
    void computerTurn();
};

#endif // GAME_H
