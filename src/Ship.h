#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <set>

class Ship {
protected:
    std::string shipName;
    int         shipPrice;
    int         shipHealth;
    std::set<int> elementSet;

public:
    Ship(const std::string& shipName, int shipPrice);
    virtual ~Ship() = default;
    Ship(int row, int col, int vida, int damage, int level);

    virtual int  search(int target) = 0;
    virtual void insert(int element) = 0;
    virtual void remove(int element) = 0;

    virtual void logOperation(const std::string& operationType, int iterationCount, double executionTime);
    int calculateDamage(int iterationCount);

    const std::string& getName()  const;
    int                getPrice() const;
};

#endif // SHIP_H
