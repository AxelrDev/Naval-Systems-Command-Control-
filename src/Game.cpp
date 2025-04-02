#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(int rows, int cols, int numShips) : rows(rows), cols(cols), numShips(numShips) {
    player = new Player(rows, cols);
    computer = new Player(rows, cols);
    player->placeShips(numShips,0);
    computer->placeShips(numShips,0);
}

Game::~Game() {
    delete player;
    delete computer;
}

void Game::play() {
    while (true) {
        std::cout << "\n----- TU TURNO -----" << std::endl;
        std::cout << "\nTu tablero propio:" << std::endl;
        player->displayOwnBoard();
        std::cout << "\nTu tablero de disparos:" << std::endl;
        player->displayTrackingBoard();

        // El jugador dispara a la computadora.
        playerTurn();
        if (computer->allShipsSunk()) {
            std::cout << "\n¡Felicidades! Has hundido todos los barcos de la computadora." << std::endl;
            break;
        }
        
        std::cout << "\n----- TURNO DE LA COMPUTADORA -----" << std::endl;
        // La computadora dispara al jugador.
        computerTurn();
        if (player->allShipsSunk()) {
            std::cout << "\n¡Oh no! La computadora ha hundido todos tus barcos." << std::endl;
            break;
        }
    }
}

void Game::playerTurn() {
    int row, col;
    std::cout << "Ingresa la fila y columna para disparar: \n";
    std::cin >> row >> col;
    // La computadora procesa el disparo en su tablero propio.
    bool hit = computer->receiveShot(row, col);
    // El jugador registra el resultado del disparo en su tracking board.
    player->recordShot(row, col, hit);
}

void Game::computerTurn() {
    // Genera coordenadas aleatorias para disparar.
    int row = std::rand() % rows;
    int col = std::rand() % cols;
    std::cout << "La computadora dispara a (" << row << ", " << col << "): ";
    // El jugador procesa el disparo en su tablero propio.
    bool hit = player->receiveShot(row, col);
    // La computadora registra el disparo en su tracking board.
    computer->recordShot(row, col, hit);
}
