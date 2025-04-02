#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Ship.h"

class Player {
public:
    // Constructor que crea un jugador con tableros de tamaño rows x cols.
    Player(int rows, int cols);
    // Destructor para liberar la memoria de los tableros.
    ~Player();

    // Coloca los barcos en el tablero propio.
    void placeShips(int numShips);

    // Procesa un disparo recibido en el tablero propio (por parte del oponente).
    bool receiveShot(int row, int col);

    // Registra un disparo al oponente en el tablero de disparos.
    void recordShot(int row, int col, bool hit);

    // Muestra el tablero propio.
    void displayOwnBoard() const;

    // Muestra el tablero de disparos (tracking board).
    void displayTrackingBoard() const;

    // Retorna true si todos los barcos han sido hundidos.
    bool allShipsSunk() const;

private:
    int rows;
    int cols;
    char **ownBoard;      // Tablero donde se colocan los barcos y se reciben disparos.
    char **trackingBoard; // Tablero para registrar los disparos realizados al oponente.
    std::vector<Ship> ships;

    // Inicializa ambos tableros llenándolos de agua ('-').
    void initializeBoards();
};

#endif // PLAYER_H
