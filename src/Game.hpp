#ifndef GAME_HPP
#define GAME_HPP

#include "Currency.hpp"
#include "Player.hpp"

class Game {
public:
    // Constructor: recibe las dimensiones del tablero y el número de barcos.
    Game(int rows, int cols, int numShips, int increment);
    ~Game();
    // Inicia el juego (modo jugador contra jugador).
    void play();
    
private:
    int rows;
    int cols;
    int numShips;
    int increment;
    Player* player1;
    Player* player2;
    Currency* currency;
    
    // Procesa el turno de un jugador. 'current' es el jugador activo y 'opponent' su rival.
    void playerTurn(Player* current, Player* opponent);
};

#endif // GAME_HPP
