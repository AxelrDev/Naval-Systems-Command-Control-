#ifndef CONSTANTS_H
#define CONSTANTS_H

// Número de elementos que se inicializan aleatoriamente en cada barco
constexpr int NUM_OF_ELEMENTS    = 100;

constexpr int MAX_NUM_ELEMENTS   = NUM_OF_ELEMENTS * 2;

// Moneda que recibe cada jugador por turno
constexpr int CURRENCY_PER_TURN  = 50;

// Precios de cada barco
constexpr int PRICE_LINEAR_SEARCH   = 100;
constexpr int PRICE_BINARY_SEARCH   = 110;
constexpr int PRICE_SET             = 120;
constexpr int PRICE_REDBLACK_TREE   = 150;
constexpr int PRICE_SPLAY_TREE      = 160;

// Constante usada para calcular daño: DAMAGE = DAMAGE_CONSTANT / iterations
constexpr int DAMAGE_CONSTANT       = 1000;
constexpr int LIFE                  = 1000;

#endif // CONSTANTS_H
