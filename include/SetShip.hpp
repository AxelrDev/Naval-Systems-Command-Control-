#ifndef SETSHIP_HPP
#define SETSHIP_HPP

#include "Ship.hpp"

class SetShip : public Ship {
private:
    int* elementsArray;
    int  elementCount;
    int  maxCapacity;

    int findIndex(int element);
    void generateElements();

public:
    SetShip();
    ~SetShip();

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // SETSHIP_HPP
