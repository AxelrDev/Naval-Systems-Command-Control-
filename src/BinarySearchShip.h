#ifndef BINARYSEARCHSHIP_H
#define BINARYSEARCHSHIP_H

#include "Ship.h"

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

#endif // BINARYSEARCHSHIP_H
