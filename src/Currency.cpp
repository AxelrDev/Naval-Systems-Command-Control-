#include "Currency.hpp"

Currency::Currency() {
    shipcost = {PRICE_LINEAR_SEARCH,PRICE_BINARY_SEARCH,PRICE_BTHREE,
        PRICE_SPLAY_TREE,PRICE_REDBLACK_TREE,PRICE_SET};
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