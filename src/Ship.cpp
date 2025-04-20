#include "Ship.hpp"
#include "Constants.hpp"
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
            << std::fixed << std::setprecision(12)
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




int Ship::getElementInSet(){
  int element = -1;
  if (elementSet.empty()) {
    std::cerr << "Error: elementSet está vacío.\n";
    return -1; // o lanzar una excepción si preferís
  }
  
  while(elementSet.find(element) == elementSet.end()){
    element = generateRandom(0,999);
  }
  return element;
}

int64_t Ship::generateRandom(int64_t min, int64_t max){
  static thread_local std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(rng);
}