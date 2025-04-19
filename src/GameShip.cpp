#include "GameShip.hpp"


GameShip::GameShip(int row, int col, int vida, int damage, int level)
    : row(row), col(col), vida(vida), damage(damage),
    
    level(level) {
        empty = false;
    }

GameShip::GameShip() : row(-1), col(-1), vida(0), damage(0), level(-1) {
    empty = true;
}
bool GameShip::occupies(int r, int c) const {
    return (r == row && c == col);
}

bool GameShip::applyDamage(int damageAmount) {
    vida -= damageAmount;
    if (vida <= 0) {
        vida = 0;
    return (vida == 0);
    }
    return false;
}

int GameShip::getVida() const {
    return vida;
}

int GameShip::getDamage() const {
    return damage;
}

int GameShip::getRow() const {
    return row;
}

int GameShip::getCol() const {
    return col;
}

void GameShip::setPosition(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

int GameShip::getLevel() {
    return level;
}

bool GameShip::getEmpty() {
    return empty;
}
void GameShip::setEmpty(bool empty) {
    this->empty = empty;
}

