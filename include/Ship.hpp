#ifndef SHIP_HPP
#define SHIP_HPP

/**
 * @file Ship.hpp
 * @brief Declares the abstract base class Ship, representing a general ship interface.
 */

#include <string>
#include <set>
#include <random>

/**
 * @class Ship
 * @brief Abstract base class for all ships, defining common functionality and interface.
 */
class Ship {
protected:
    std::string shipName;      ///< Name of the ship
    int shipPrice;             ///< Price of the ship
    int shipHealth;            ///< Health of the ship
    std::set<int> elementSet;  ///< Set of elements stored in the ship
    int iterations;            ///< Iteration counter for operations

public:
    /**
     * @brief Constructs a Ship with a name and price.
     * @param shipName Name of the ship.
     * @param shipPrice Cost of the ship.
     */
    Ship(const std::string& shipName, int shipPrice);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Ship() = default;

    /**
     * @brief Extended constructor (used in derived classes like GameShip).
     */
    Ship(int row, int col, int vida, int damage, int level);

    /**
     * @brief Searches for a target value in the ship's data structure.
     * @param target Value to search.
     * @return Number of iterations performed.
     */
    virtual int search(int target) = 0;

    /**
     * @brief Inserts a new value into the ship's data structure.
     * @param element Value to insert.
     */
    virtual void insert(int element) = 0;

    /**
     * @brief Removes a value from the ship's data structure.
     * @param element Value to remove.
     */
    virtual void remove(int element) = 0;

    /**
     * @brief Logs the operation details like type, iteration count, and execution time.
     * @param operationType Type of the operation (e.g., "insert", "search").
     * @param iterationCount Number of iterations performed.
     * @param executionTime Duration of the operation in seconds.
     */
    virtual void logOperation(const std::string& operationType, int iterationCount, double executionTime);

    /**
     * @brief Calculates the damage based on the number of iterations.
     * @param iterationCount Number of iterations.
     * @return Damage value.
     */
    int calculateDamage(int iterationCount);

    /**
     * @brief Gets the ship's name.
     * @return Reference to the ship name string.
     */
    const std::string& getName() const;

    /**
     * @brief Gets the price of the ship.
     * @return Price value.
     */
    int getPrice() const;

    /**
     * @brief Retrieves a random element from the ship.
     * @return Element value.
     */
    int getElement();

    /**
     * @brief Retrieves an element specifically from the set container.
     * @return Element value.
     */
    int getElementInSet();

    /**
     * @brief Generates a random integer in a given range.
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Random integer between min and max.
     */
    int64_t generateRandom(int64_t min, int64_t max);
};

#endif // SHIP_HPP