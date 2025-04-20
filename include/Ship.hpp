#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <set>
#include <random>

class Ship {
protected:
    std::string shipName;
    int         shipPrice;
    int         shipHealth;
    std::set<int> elementSet;
    int iterations;

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
    int getElement();
    int getElementInSet();
    int64_t generateRandom(int64_t min, int64_t max);
};

#endif // SHIP_HPP
