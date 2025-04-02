#include "Player.h"
#include <iostream>
#include <cstdlib>

// Constructor: asigna memoria para ambos tableros y los inicializa.
Player::Player(int rows, int cols) : rows(rows), cols(cols) {
    // Asignación dinámica para el tablero propio y el de disparos (trackingBoard)
    ownBoard = new char*[rows];
    trackingBoard = new char*[rows];
    for (int i = 0; i < rows; i++) {
        ownBoard[i] = new char[cols];
        trackingBoard[i] = new char[cols];
    }
    initializeBoards();
}

// Destructor: libera la memoria asignada a ambos tableros.
Player::~Player() {
    for (int i = 0; i < rows; i++) {
        delete[] ownBoard[i];
        delete[] trackingBoard[i];
    }
    delete[] ownBoard;
    delete[] trackingBoard;
}

// Inicializa ambos tableros con el carácter '-' (agua).
void Player::initializeBoards() {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            ownBoard[i][j] = '-';
            trackingBoard[i][j] = '-';
        }
    }
}

// Coloca numShips barcos de tamaño variable (entre 1 y 5 celdas) en el tablero propio.
// Se verifica que las celdas estén libres y que el barco no se salga del tablero.
void Player::placeShips(int numShips, int sizeShip) {
    int placed = 0;
    while (placed < numShips) {
        int length;
        if(numShips == 1){
            if(sizeShip){
                length = sizeShip;
            }else{
                // Tamaño aleatorio entre 1 y 5
                length = 1 + std::rand() % 5;
            }
        }else{
            // Tamaño aleatorio entre 1 y 5
            length = 1 + std::rand() % 5;
        }
        // Orientación aleatoria: true para horizontal, false para vertical
        bool horizontal = (std::rand() % 2) == 0;
        int r, c;
        if (horizontal) {
            r = std::rand() % rows;
            c = std::rand() % (cols - length + 1);
        } else {
            r = std::rand() % (rows - length + 1);
            c = std::rand() % cols;
        }
        
        // Verifica que todas las celdas donde se quiere colocar el barco estén libres
        bool canPlace = true;
        if (horizontal) {
            for (int j = 0; j < length; j++) {
                if (ownBoard[r][c + j] != '-') {
                    canPlace = false;
                    break;
                }
            }
        } else {
            for (int i = 0; i < length; i++) {
                if (ownBoard[r + i][c] != '-') {
                    canPlace = false;
                    break;
                }
            }
        }
        
        // Si es posible colocar el barco, se marca en el tablero propio y se añade al vector de barcos.
        if (canPlace) {
            if (horizontal) {
                for (int j = 0; j < length; j++) {
                    ownBoard[r][c + j] = 'S';
                }
            } else {
                for (int i = 0; i < length; i++) {
                    ownBoard[r + i][c] = 'S';
                }
            }
            ships.push_back(Ship(r, c, length, horizontal));
            placed++;
        }
    }
}

// Procesa un disparo recibido en el tablero propio (disparo del oponente).
// Si se impacta un barco, se actualiza la celda a 'X' y se marca el impacto en el barco correspondiente.
// Si se dispara al agua, se marca la celda con 'O'.
bool Player::receiveShot(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cout << "¡Disparo fuera de límites!" << std::endl;
        return false;
    }
    if (ownBoard[row][col] == 'X' || ownBoard[row][col] == 'O') {
        std::cout << "¡Ya se ha disparado en esta posición!" << std::endl;
        return false;
    }
    if (ownBoard[row][col] == 'S') {
        // Busca el barco que ocupa la celda y procesa el impacto.
        for (auto &ship : ships) {
            if (ship.occupies(row, col)) {
                if (ship.hitAt(row, col)) {
                    ownBoard[row][col] = 'X';
                    std::cout << "¡Impacto!" << std::endl;
                    return true;
                }
            }
        }
        // Caso por defecto, marca la celda como impacto.
        ownBoard[row][col] = 'X';
        std::cout << "¡Impacto!" << std::endl;
        return true;
    } else if (ownBoard[row][col] == '-') {
        ownBoard[row][col] = 'O';
        std::cout << "Agua." << std::endl;
        return false;
    }
    return false;
}

// Registra en el tablero de disparos (trackingBoard) el resultado de un disparo realizado al oponente.
// Se coloca 'X' si fue impacto o 'O' si fue agua.
void Player::recordShot(int row, int col, bool hit) {
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return;
    trackingBoard[row][col] = hit ? 'X' : 'O';
}

// Muestra el tablero propio (donde se encuentran los barcos y se registran los disparos del oponente).
void Player::displayOwnBoard() const {
    std::cout << "Tablero propio:" << std::endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << ownBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Muestra el tablero de disparos (tracking board) con los tiros realizados al oponente.
void Player::displayTrackingBoard() const {
    std::cout << "Tablero de disparos:" << std::endl;
    std::cout << "  0 1 2 3 4 5 6 7 8 9"<< std::endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols+1; j++){
            if(j==0){
                std::cout << i <<" " ;
            }
            std::cout <<trackingBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Retorna true si todos los barcos han sido hundidos.
bool Player::allShipsSunk() const {
    for (const auto &ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}
