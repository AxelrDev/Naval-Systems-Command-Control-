#include "Player.hpp"
#include <iostream>
#include <cstdlib>

Player::Player(int rows, int cols) : rows(rows), cols(cols) {  // Ejemplo: 3 acciones por turno.
    ownBoard = new int*[rows];
    changeMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        ownBoard[i] = new int[cols];
        changeMatrix[i] = new int[cols];
    }
    initializeBoards();
    money = 1000;
    improvementPoints = 0; // Inicializa los puntos de mejora.
    shipStorage = Ship(); // Marca el barco como vacío.
}

Player::~Player() {
    for (int i = 0; i < rows; i++) {
        delete[] ownBoard[i];
        delete[] changeMatrix[i];
    }
    delete[] ownBoard;
    delete[] changeMatrix;
}

void Player::initializeBoards() {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            ownBoard[i][j] = -1;
            changeMatrix[i][j] = -1;
        }
    }
}

void Player::placeShips(int numShips, int levelShip) {
    // En este ejemplo, se ignora 'mode'. Se colocan barcos de tamaño 1.
    for(int index = 0; index < numShips; index++){
        int r = std::rand() % rows;
        int c = std::rand() % cols;
        int level;
        if (levelShip == -1) {
            level = std::rand() % 6; // Asignar un nivel aleatorio entre 1 y 6.
        } 
        if (ownBoard[r][c] == -1) {
            // Se asignan valores por defecto: vida = 3, daño = 1.
            ships.push_back(Ship(r, c, 3, 1, level));
            for (size_t i = 0; i < ships.size(); i++) {
                if (ships[i].occupies(r, c)) {
                    ownBoard[r][c] = ships[i].getLevel(); // Se asigna el nivel del barco a la posición.
                }
            }
            
        }
    }
}

bool Player::receiveShot(int row, int col, int damage) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cout << "¡Disparo fuera de límites!" << std::endl;
        return false;
    }
    // Si ya se disparó en esta celda.
    // if (ownBoard[row][col] == 'X' || ownBoard[row][col] == 'O') {
       // std::cout << "¡Ya se disparó en esa posición!" << std::endl;
     // return false;
    // }
    if (ownBoard[row][col] >= 0 && ownBoard[row][col] <= 5) {
        // Buscar el barco que ocupa esta celda.
        for (size_t i = 0; i < ships.size(); i++) {
            if (ships[i].occupies(row, col)) {
                bool sunk = ships[i].applyDamage(damage);  // Se aplica 1 punto de daño.
                if (sunk) {
                    ownBoard[row][col] = -1;
                    std::cout << "¡Impacto y barco hundido!" << std::endl;
                } else {
                    // ownBoard[row][col] = 'D';  // 'D' indica que fue dañado.
                    std::cout << "¡Impacto!" << std::endl;
                }
                return true;
            }
        }
    } else {
        if (ownBoard[row][col] == -1) {
            // ownBoard[row][col] = 'O';
            std::cout << "¡Agua!" << std::endl;
            return false;
        }
    }
    return false;
}
// No usar esta función.
void Player::recordShot(int row, int col, bool hit) {
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return;
    changeMatrix[row][col] = hit ? 'X' : 'O';
}

void Player::displayOwnBoard() {
    std::cout << "  0 1 2 3 4 5 6 7 8 9"<< std::endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(j==0){
                std::cout << i <<" " ;
            }
            std::cout << ownBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Player::getShipDamage(int row, int col) {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].occupies(row, col)) {
            return ships[i].getDamage();
        }
    }
    return -1; // No hay barco en esa posición.
}

void Player::displayTrackingBoard() {
    std::cout << "  0 1 2 3 4 5 6 7 8 9"<< std::endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(j==0){
                std::cout << i <<" " ;
            }
            std::cout << changeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Player::allShipsSunk() {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].getVida() > 0)
            return false;
    }
    return true;
}

int Player::getaction() {
    return actions;
}

void Player::setLessAction() {
    if (actions > 0)
        actions--;
}

void Player::setaction(int newAction) {
    actions = newAction;
}

bool Player::moveShip() {
    int r, c;
    std::cout << "Ingrese la fila y columna del barco a mover: ";
    std::cin >> r >> c;
    int shipIndex = -1;
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].occupies(r, c)) {
            shipIndex = i;
            break;
        }
    }
    if (shipIndex == -1) {
        std::cout << "No se encontró ningún barco en esa posición." << std::endl;
        return false;
    }
    // Quitar el barco del tablero actual.
    Ship &shipToMove = ships[shipIndex];
    int oldRow = shipToMove.getRow();
    int oldCol = shipToMove.getCol();
    ownBoard[oldRow][oldCol] = -1 ;
    
    int newRow, newCol;
    std::cout << "Ingrese la nueva fila y columna para el barco: ";
    std::cin >> newRow >> newCol;
    if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || ownBoard[newRow][newCol] != -1) {
        std::cout << "Posición inválida o ya ocupada." << std::endl;
        // Restaura la posición original.
        ownBoard[oldRow][oldCol] = shipToMove.getLevel();
        return false;
    }
    // Coloca el barco en la nueva posición y actualiza su información.
    shipToMove.setPosition(newRow, newCol);
    ownBoard[newRow][newCol] = shipToMove.getLevel();
    std::cout << "Barco movido exitosamente." << std::endl;
    return true;
}

int Player::getMoney() {
    return money;
}

bool Player::lessMoney(int amount) {
    money -= amount;
    if(money < 0) {
        return false; // No hay suficiente dinero
    }
    return true; // Dinero suficiente
}

void Player::plusMoney(int amount) {
    money += amount;
}

void Player::upGradeShip(int row, int col) {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].occupies(row, col)) {
            // ships[i].upgrade();
        } else {
            std::cout << "No hay barco en esa posición." << std::endl;
        }
    }
}

int** Player::getboard() {
    return ownBoard;
}



int** Player::getTrackingBoard() {
    return changeMatrix;
}

bool Player::isShipempty() {
    if(shipStorage.getEmpty()) {
        return true; // El barco está vacío
    }else {
        return false; // El barco no está vacío
    }
}


Ship Player::getShipStorage() {
    return shipStorage;
}
void Player::setShipStorage(Ship ship) {
    shipStorage = ship;
}

std::vector<Ship>& Player::getShips() {
    return ships;
}

void Player::setShipStorageEmpty() {
    shipStorage.setEmpty(true);
}

void Player::attackMatrix() {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            changeMatrix[i][j] = -1;
        }
    }
}

void Player::setPlayerBoard() {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            changeMatrix[i][j] = ownBoard[i][j];
        }
    }
}

int **Player::getChangeMatrix() {
    return changeMatrix;
}

void Player::plusImprovementPoints() {
    improvementPoints++;
}