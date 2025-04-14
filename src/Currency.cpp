#include "Currency.hpp"

Currency::Currency() {
    ship01 = 100;
    ship02 = 200;
    ship03 = 300;
    ship04 = 400;
    ship05 = 500;
    ship06 = 600;
}
// Currency::~Currency() {}

int Currency::getShip(int number) {
    if (number < 1 || number > 6) {
        std::cerr << "Número de barco inválido. Debe estar entre 1 y 6." << std::endl;
        return -1; // Valor de error
    } else {
        if (number == 1) {
            return ship01;
        } else if (number == 2) {
            return ship02;
        } else if (number == 3) {
            return ship03;
        } else if (number == 4) {
            return ship04;
        } else if (number == 5) {
            return ship05;
        } else if (number == 6) {
            return ship06;
        }
    }
    return -1; // Valor de error
}
