#include "GameShip.hpp"


GameShip::GameShip(int row, int col, int vida, int damage, int level)
    : row(row), col(col), vida(vida), damage(damage),level(level){
        empty = false;
        typeOfShip();
    }

GameShip::GameShip() : row(-1), col(-1), vida(0), damage(0), level(-1) {
    empty = true;
    typeShip = nullptr;
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
    printf(typeShip->getName().c_str());
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

void GameShip::typeOfShip(){
    if(level == 0){
        typeShip = new LinearSearchShip();
    }else if(level == 1){
        typeShip = new BinarySearchShip();
    }else if(level == 2){
        typeShip = new BTreeShip();
    }else if(level == 3){
        typeShip = new SplayTreeShip();
    }else if(level == 4){
        typeShip = new SetShip();
    }else if(level == 5){
        typeShip =  new SetShip();
    }
}

Ship * GameShip::getTypeShip(){
    return typeShip;
}