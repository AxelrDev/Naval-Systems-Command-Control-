#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <iostream>
#include <vector>   

class Currency {
    public:
    Currency();
   // ~Currency();
    int getShip(int number);
    int canBuy(int cash, int cost);
    private:
    std::vector<int> shipcost;
};

#endif // CURRENCY_HPP