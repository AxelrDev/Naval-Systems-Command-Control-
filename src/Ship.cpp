#include "Ship.hpp"

Ship::Ship(int row, int col, int vida, int damage, int level)
    : row(row), col(col), vida(vida), damage(damage), level(level) {}

bool Ship::occupies(int r, int c) const {
    return (r == row && c == col);
}

bool Ship::applyDamage(int damageAmount) {
    vida -= damageAmount;
    if (vida < 0)
        vida = 0;
    return (vida == 0);
}

int Ship::getVida() const {
    return vida;
}

int Ship::getDamage() const {
    return damage;
}

int Ship::getRow() const {
    return row;
}

int Ship::getCol() const {
    return col;
}

void Ship::setPosition(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

int Ship::getLevel() {
    return level;
}
