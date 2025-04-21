#ifndef SETSHIP_HPP
#define SETSHIP_HPP

/**
 * @file SetShip.hpp
 * @brief Declares the SetShip class that simulates set-like behavior using a dynamic array.
 */

#include "Ship.hpp"

/**
 * @class SetShip
 * @brief A ship implementation using an array with unique elements, mimicking a set structure.
 */
class SetShip : public Ship {
private:
    int* elementsArray;   ///< Dynamic array storing the elements
    int  elementCount;    ///< Current number of elements
    int  maxCapacity;     ///< Maximum capacity of the array

    /**
     * @brief Finds the index of an element in the array.
     * @param element Value to find.
     * @return Index if found, -1 otherwise.
     */
    int findIndex(int element);

    /**
     * @brief Populates the array with initial unique elements.
     */
    void generateElements();

public:
    /**
     * @brief Constructs a SetShip and initializes the element array.
     */
    SetShip();

    /**
     * @brief Destructor. Frees the dynamically allocated array.
     */
    ~SetShip();

    /**
     * @brief Searches for an element in the array.
     * @param target Value to search.
     * @return Number of iterations performed.
     */
    int search(int target) override;

    /**
     * @brief Inserts a unique element into the array.
     * @param element Value to insert.
     */
    void insert(int element) override;

    /**
     * @brief Removes an element from the array.
     * @param element Value to remove.
     */
    void remove(int element) override;
};

#endif // SETSHIP_HPP