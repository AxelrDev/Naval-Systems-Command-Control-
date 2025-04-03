#ifndef SETSHIP_H
#define SETSHIP_H

#include "Ship.h"
#include <set>

class SetShip : public Ship {
private:
    std::set<int> internalSet;

public:
    SetShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif
