#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
public:
    // Constructor: recibe las dimensiones del tablero y el número de barcos.
    Game(int rows, int cols, int numShips);
    ~Game();
    // Inicia el juego (modo jugador contra jugador).
    void play();
    
private:
    int rows;
    int cols;
    int numShips;
    Player *player1;
    Player *player2;
    
    // Procesa el turno de un jugador. 'current' es el jugador activo y 'opponent' su rival.
    void playerTurn(Player* current, Player* opponent);
};

#endif // GAME_H
