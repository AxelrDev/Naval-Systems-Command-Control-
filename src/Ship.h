#ifndef SHIP_H
#define SHIP_H

#include "Includes.h"

class Ship {
protected:
    std::string name;
    int health;
    int price;
    std::vector<int> Properties; // <x,y,length> TENTATIVO Jose pablo resuelve como quiera llevarlo
    std::set<int> elementSet; //Used to check if a number is present for erasing or searching, random selecting for erasure
    std::vector<int> elements; //Used for algorithms

public:
    Ship(std::string name, int price);

    virtual ~Ship() = default;
    
    virtual int search(int target) = 0;
    virtual void insert (int element) = 0;
    virtual void remove(int element) = 0;

    virtual void upgrade();

    int getPrice()const;
    vector<int> getProperties();
    void setProperties(int x, int y, int z); // NOT FULLY IMPLEMENTED
    std::string getName() const;

    virtual void logOperation(const std::string& type, int iterations, double time); // NOT FULLY IMPLEMENTED
};

#endif