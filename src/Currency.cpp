#include "Currency.hpp"

Currency::Currency() {
    shipcost = {100,200,300,400,500,600};
}
// Currency::~Currency() {}

int Currency::getShip(int number) {
    return shipcost.at(number);
}

int Currency::canBuy(int cash, int cost){
    int sell = cash - cost;
    if(sell<0){
        return -1;
    }
    return cost;
}
