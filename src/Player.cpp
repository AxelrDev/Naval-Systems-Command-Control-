#include "Player.hpp"
#include <iostream>
#include <cstdlib>
#include "Constants.hpp"

Player::Player(int rows, int cols) : rows(rows), cols(cols) {  // Ejemplo: 3 acciones por turno.
    ownBoard = new int*[rows];
    changeMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        ownBoard[i] = new int[cols];
        changeMatrix[i] = new int[cols];
    }
    initializeBoards();
    money = MONEY;
    improvementPoints = 0; 
    shipStorage = GameShip();
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
    int barcosColocados = 0;

    while (barcosColocados < numShips) {
        int r = std::rand() % rows;
        int c = std::rand() % cols;

        if (ownBoard[r][c] == -1) {
            int level;
            if (levelShip == -1) {
                level = std::rand() % 6;
            }
            ships.push_back(GameShip(r, c, LIFE, DAMAGE_CONSTANT, level));
            ownBoard[r][c] = level;
            barcosColocados++;
        }

    }
}

bool Player::receiveShot(int row, int col, int damage) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    if (ownBoard[row][col] >= 0 && ownBoard[row][col] <= 5) {
        for (size_t i = 0; i < ships.size(); i++) {
            if (ships[i].occupies(row, col)) {
                bool sunk = ships[i].applyDamage(damage); 
                if (sunk) {
                    ownBoard[row][col] = -1;
                    //std::cout << "¡Impacto y barco hundido!" << std::endl;
                    ships.erase(ships.begin()+i);
                } else {
                    //std::cout << "¡Impacto!" << std::endl;
                }
                return true;
            }
        }
    } else {
        if (ownBoard[row][col] == -1) {
            // ownBoard[row][col] = 'O';
            //std::cout << "¡Agua!" << std::endl;
            return false;
        }
    }
    return false;
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
            int dam = ships[i].getTypeShip()->calculateDamage(ships[i].getTypeShip()->search(ships[i].getTypeShip()->getElementInSet()));
            return dam;
        }
    }
    return -1;
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
            ships[i].getTypeShip()->remove(ships[i].getTypeShip()->getElementInSet());
        } else {
            //std::cout << "No hay barco en esa posición." << std::endl;
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
        return true;
    }else {
        return false;
    }
}


GameShip Player::getShipStorage() {
    return shipStorage;
}
void Player::setShipStorage(GameShip ship) {
    shipStorage = ship;
}

std::vector<GameShip>& Player::getShips() {
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

int Player::getImprovementPoints() {
    return improvementPoints;
}