#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "Ship.hpp"

class Player {
public:
    // Constructor y destructor.
    Player(int rows, int cols);
    ~Player();

    // Coloca numShips barcos de una sola celda en posiciones aleatorias.
    // El parámetro mode se incluye para compatibilidad (se puede ignorar en este ejemplo).
    void placeShips(int numShips, int levelShip);
    
    // Procesa un disparo recibido en (row, col) en el tablero propio.
    // Si hay un barco, se le aplica daño (se asume daño 1 por disparo).
    // Se marca 'X' si se hunde, o 'D' si se impacta pero aún queda vida.
    // Si se dispara al agua, se marca 'O'.
    bool receiveShot(int row, int col, int damage);
    
    // Registra el resultado del disparo realizado al oponente en el tracking board.
    void recordShot(int row, int col, bool hit);
    int getShipDamage(int row, int col);

    // Visualiza el tablero propio y el tablero de disparos.
    void displayOwnBoard();
    void displayTrackingBoard();
    
    // Retorna true si todos los barcos están hundidos (vida == 0).
    bool allShipsSunk();
    
    // Métodos para gestionar el número de acciones por turno.
    int getaction();
    void setLessAction();
    void setaction(int newAction);
    
    // Permite mover un barco: quita el barco de su posición actual y lo coloca en una nueva posición.
    bool moveShip();

    // Muestra la cantidad de dinero disponible.
    int getMoney();

    // Resta el costo del barco con el dinero que tiene.
    bool lessMoney(int amount);

    // Suma el dinero al total del jugador.
    void plusMoney(int amount);

    // Mejorar el barco en la posición (row, col).
    void upGradeShip(int row, int col);

    int** getboard();
    int** getTrackingBoard();

    bool Shipempty(Player* player);
    Ship* getShipStorage();
    void setShipStorage(Ship* ship);
    std::vector<Ship>& getShips();

private:
    int rows;
    int cols;
    // Dinero en el juego
    int money;
    int** ownBoard;      // Tablero donde se ubican los barcos del jugador.
    int** trackingBoard; // Tablero para registrar los disparos realizados al oponente.
    std::vector<Ship> ships;  // Vector con los barcos del jugador.
    Ship* shipStorage; 
    
    int actions;  // Acciones disponibles en el turno.
    
    // Inicializa ambos tableros llenándolos con '-'
    void initializeBoards();
};

#endif // PLAYER_HPP
