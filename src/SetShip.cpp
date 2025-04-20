#include "SetShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

SetShip::SetShip()
  : Ship("Set", PRICE_SET),
    elementCount(0), maxCapacity(MAX_NUM_ELEMENTS)
{
    elementsArray = new int[maxCapacity];
    generateElements();
}

SetShip::~SetShip() {
    delete[] elementsArray;
}

int SetShip::findIndex(int element) {
    int leftIndex  = 0;
    int rightIndex = elementCount - 1;
    while (leftIndex <= rightIndex) {
        int middleIndex = (leftIndex + rightIndex) / 2;
        if      (elementsArray[middleIndex] == element)
            return middleIndex;
        else if (elementsArray[middleIndex] < element)
            leftIndex = middleIndex + 1;
        else
            rightIndex = middleIndex - 1;
    }
    return -1;
}

int SetShip::search(int target) {
    int iterationCount = 0;
    int leftIndex  = 0;
    int rightIndex = elementCount - 1;

    auto startTime = std::chrono::high_resolution_clock::now();
    while (leftIndex <= rightIndex) {
        ++iterationCount;
        int middleIndex = (leftIndex + rightIndex) / 2;
        if      (elementsArray[middleIndex] == target)
            break;
        else if (elementsArray[middleIndex] < target)
            leftIndex = middleIndex + 1;
        else
            rightIndex = middleIndex - 1;
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    double executionTime =
      std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, executionTime);
    return iterationCount;
}

void SetShip::insert(int element) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    // If already present, nothing to do
    if (findIndex(element) != -1) {
        double executionTime =
          std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - startTime
          ).count();
        logOperation("insert", iterationCount, executionTime);
        return;
    }

    // Shift right until we find the insertion point
    int currentIndex = elementCount - 1;
    while (currentIndex >= 0 && elementsArray[currentIndex] > element) {
        ++iterationCount;
        elementsArray[currentIndex + 1] = elementsArray[currentIndex];
        --currentIndex;
    }
    elementsArray[currentIndex + 1] = element;
    ++elementCount;
    iterationCount++;
    elementSet.insert(element);

    auto endTime = std::chrono::high_resolution_clock::now();
    double executionTime =
      std::chrono::duration<double>(endTime - startTime).count();
    logOperation("insert", iterationCount, executionTime);
}

void SetShip::remove(int element) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    int foundIndex = findIndex(element);
    if (foundIndex == -1) {
        double executionTime =
          std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - startTime
          ).count();
        logOperation("remove", iterationCount, executionTime);
        return;
    }

    // Shift left to overwrite the removed slot
    for (int currentIndex = foundIndex; currentIndex < elementCount - 1; ++currentIndex) {
        ++iterationCount;
        elementsArray[currentIndex] = elementsArray[currentIndex + 1];
    }
    --elementCount;
    elementSet.erase(element);

    auto endTime = std::chrono::high_resolution_clock::now();
    double executionTime =
      std::chrono::duration<double>(endTime - startTime).count();
    logOperation("remove", iterationCount, executionTime);
}

void SetShip::generateElements(){
    int elements = 0;
    while(elements < NUM_OF_ELEMENTS){
      int value = generateRandom(0,MAX_NUM_ELEMENTS);
      if(elementSet.find(value) == elementSet.end()){
        insert(value);
        elements ++;
      }
    }
  }