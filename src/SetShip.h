#ifndef SETSHIP_H
#define SETSHIP_H

#include "Ship.h"

class SetShip : public Ship {
private:
    int* elementsArray;
    int  elementCount;
    int  maxCapacity;

    int findIndex(int element);

public:
    SetShip();
    ~SetShip();

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // SETSHIP_H
