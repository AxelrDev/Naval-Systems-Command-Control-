#ifndef BINARYSEARCHSHIP_HPP
#define BINARYSEARCHSHIP_HPP

#include "Ship.hpp"

class BinarySearchShip : public Ship {
private:
    int* elementsArray;
    int  elementCount;
    int  maxCapacity;

    void sortArray();

public:
    BinarySearchShip();
    ~BinarySearchShip();

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // BINARYSEARCHSHIP_HPP
