#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(int rows, int cols, int numShips, int increment)
    : rows(rows), cols(cols), numShips(numShips), increment(increment) {
    // Se crean dos jugadores.
    player1 = new Player(rows, cols);
    player2 = new Player(rows, cols);
    // Se colocan los barcos en ambos tableros.
    player1->placeShips(numShips);
    player2->placeShips(numShips);
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::play() {
    // Se asignan, por ejemplo, 3 acciones por turno a cada jugador.
    player1->setaction(3);
    player2->setaction(3);
    while (true) {

        std::cout << "\n----- TURNO DEL JUGADOR 1 -----" << std::endl;
        std::cout << "\nTablero propio (Jugador 1):" << std::endl;
        player1->displayOwnBoard();
        std::cout << "\nTablero de disparos (Jugador 1):" << std::endl;
        player1->displayTrackingBoard();

        playerTurn(player1, player2);
        if (player2->allShipsSunk()) {
            std::cout << "\n¡Felicidades! Jugador 1 ha hundido todos los barcos de Jugador 2." << std::endl;
            break;
        }
        // Reinicia las acciones para el otro jugador.
        player2->setaction(3);
        
        std::cout << "\n----- TURNO DEL JUGADOR 2 -----" << std::endl;
        std::cout << "\nTablero propio (Jugador 2):" << std::endl;
        player2->displayOwnBoard();
        std::cout << "\nTablero de disparos (Jugador 2):" << std::endl;
        player2->displayTrackingBoard();

        playerTurn(player2, player1);
        if (player1->allShipsSunk()) {
            std::cout << "\n¡Felicidades! Jugador 2 ha hundido todos los barcos de Jugador 1." << std::endl;
            break;
        }
        player1->setaction(3);
    }
}

void Game::playerTurn(Player* current, Player* opponent) {
    int action = current->getaction();
    int option;
    while (action > 0) {
        std::cout << "\n Dinero actual: " << current->getMoney() << std::endl;
        std::cout << "\nAcciones restantes: " << current->getaction() << std::endl;
        std::cout << "1. Atacar" << std::endl;
        //  (no implementado)
        std::cout << "2. Upgrade ship" << std::endl;
        std::cout << "3. Buy ship" << std::endl;
        std::cout << "4. Mover barco" << std::endl;
        std::cout << "5. Terminar turno" << std::endl;
        std::cout << "Ingrese el número de opción: ";
        std::cin >> option;
        // Atacar
        if (option == 1) {
            int row, col, rowShip, colShip, damage;
            std::cout << "Ingrese la fila y columna del barco desde el cual desea atacar: \n";
            std::cin >> rowShip >> colShip;
            damage = current->getShipDamage(rowShip, colShip);
            if (damage == -1) {
                std::cout << "No hay barcos en esa posición." << std::endl;
            } else {
                std::cout << "Ingrese la fila y columna para atacar: \n";
                std::cin >> row >> col;
                bool hit = opponent->receiveShot(row, col, damage, increment, current);
                current->recordShot(row, col, hit);
                current->setLessAction();
            }
        } else 
            // Upgrade ship
            if (option == 2) {
                // se debe de agregar la posicion del barco. 
                current->upGradeShip(1,1);
                current->setLessAction();
        } else 
            // Buy ship
            if (option == 3) {
                current->placeShips(1);
                
                current->setLessAction();
        } else 
            // Move ship
            if (option == 4) {
                if (current->moveShip()) {
                    current->setLessAction();
                }
        } else 
            // Terminar turno
            if (option == 5) {
                current->setaction(0);
                break;
        } else {
            // Para opciones 2 y 3, se resta una acción (lógica pendiente de implementar).
            current->setLessAction();
        }
        action = current->getaction();
    }
}
