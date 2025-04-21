#ifndef BINARYSEARCHSHIP_HPP
#define BINARYSEARCHSHIP_HPP

#include "Ship.hpp"

/**
 * @class BinarySearchShip
 * @brief A ship implementation that uses binary search on a dynamic array.
 */
class BinarySearchShip : public Ship {
private:
    /**
     * @brief Dynamic array to store elements.
     */
    int* elementsArray;
    int  elementCount;
    int  maxCapacity;

    /**
     * @brief Sorts the array using insertion sort.
     * @return The number of iterations during sorting.
     */
    int sortArray();
    void generateElements();

public:
    /**
     * @brief Constructor. Initializes the array and populates it with elements.
     */
    BinarySearchShip();
    ~/**
     * @brief Constructor. Initializes the array and populates it with elements.
     */
    BinarySearchShip();

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif 