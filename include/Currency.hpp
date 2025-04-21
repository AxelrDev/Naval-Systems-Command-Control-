#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <iostream>
#include <vector>   

/**
 * @class Currency
 * @brief Manages ship costs and purchasing logic.
 */
class Currency {
public:
    /**
     * @brief Constructs the Currency object and initializes ship costs.
     */
    Currency();

    /**
     * @brief Gets the cost of a ship by index.
     * @param number Index of the ship.
     * @return Cost of the specified ship.
     */
    int getShip(int number);

    /**
     * @brief Determines whether a purchase can be made based on current cash.
     * @param cash Current amount of money.
     * @param cost Cost of the item to buy.
     * @return 1 if purchase is possible, 0 otherwise.
     */
    int canBuy(int cash, int cost);

private:
    /**
     * @brief Stores the cost of each ship.
     */
    std::vector<int> shipcost;
};

#endif // CURRENCY_HPP