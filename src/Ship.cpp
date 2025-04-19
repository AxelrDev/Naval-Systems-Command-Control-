#include "Ship.h"
#include "Constants.h"
#include <fstream>
#include <iomanip>
#include <iostream>

Ship::Ship(const std::string& shipName_, int shipPrice_)
  : shipName(shipName_), shipPrice(shipPrice_), shipHealth(100)
{}

void Ship::logOperation(const std::string& operationType,
                        int iterationCount,
                        double executionTime) {
    std::ofstream logFile("battle_log.txt", std::ios::app);
    if (!logFile) {
        std::cerr << "Error opening battle_log.txt\n";
        return;
    }
    logFile << "=== Operation Log ===\n"
            << "Ship: "      << shipName        << "\n"
            << "Operation: " << operationType   << "\n"
            << "Iterations: "<< iterationCount  << "\n"
            << std::fixed << std::setprecision(6)
            << "Time: "      << executionTime   << "s\n"
            << "Damage: "    << calculateDamage(iterationCount) << "\n"
            << "----------------------\n";
}

int Ship::calculateDamage(int iterationCount) {
    return iterationCount > 0 ? DAMAGE_CONSTANT / iterationCount : DAMAGE_CONSTANT;
}

const std::string& Ship::getName()  const {
  return shipName; 
}
int Ship::getPrice() const {
  return shipPrice;
}


int Ship::getElement(){
    bool exist = true;
    int element=0;
    while(exist){
        element = rand() % 1000;
        auto it = elementSet.find(element);
        if(it != elementSet.end()){
            exist=false;
        }
    }
    return element;
}