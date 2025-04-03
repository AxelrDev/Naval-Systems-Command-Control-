#ifndef LINEARSEARCHSHIP_H
#define LINEARSEARCHSHIP_H

#include "Ship.h"
#include <list>

class LinearSearchShip : public Ship {
private:
    std::list<int> linkedList;

public:
    LinearSearchShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif
