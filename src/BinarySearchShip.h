#ifndef BINARYSEARCHSHIP_H
#define BINARYSEARCHSHIP_H

#include "Ship.h"
#include <vector>

class BinarySearchShip : public Ship {
private:
    std::vector<int> sortedArray;

public:
    BinarySearchShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif
