#ifndef CURRENCY_H
#define CURRENCY_H

#include <iostream>

class Currency {
    public:
    Currency();
   // ~Currency();
    int getShip01();
    int getShip02();
    int getShip03();
    int getShip04();
    int getShip05();
    int getShip06();
    private:
    int ship01;
    int ship02;
    int ship03;
    int ship04;
    int ship05;
    int ship06;
};

#endif // CURRENCY_H