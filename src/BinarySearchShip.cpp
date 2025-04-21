#include "BinarySearchShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

BinarySearchShip::BinarySearchShip()
  : Ship("BinarySearch", PRICE_BINARY_SEARCH),
    elementCount(0), maxCapacity(MAX_NUM_ELEMENTS)
{
    elementsArray = new int[maxCapacity];
    generateElements();
}

BinarySearchShip::~BinarySearchShip() {
    delete[] elementsArray;
}

int BinarySearchShip::sortArray() {
    int iterationCount = 1;
    for (int i = 1; i < elementCount; ++i) {
        int keyValue = elementsArray[i];
        int j = i - 1;
        while (j >= 0 && elementsArray[j] > keyValue) {
            iterationCount++;
            elementsArray[j+1] = elementsArray[j];
            --j;
        }
        elementsArray[j+1] = keyValue;
    }
    return iterationCount;
}

int BinarySearchShip::search(int target) {
    int iterationCount = 0;
    int left = 0, right = elementCount - 1;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (left <= right) {
        ++iterationCount;
        int mid = (left + right) / 2;
        if      (elementsArray[mid] == target) break;
        else if (elementsArray[mid] <  target) left  = mid + 1;
        else                                   right = mid - 1;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void BinarySearchShip::insert(int element) {
    if (elementCount >= maxCapacity) return;
    auto startTime = std::chrono::high_resolution_clock::now();
    elementsArray[elementCount++] = element;
    elementSet.insert(element);
    int iterationCount = sortArray();
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("insert", iterationCount, execTime);
}

void BinarySearchShip::remove(int element) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < elementCount; ++i) {
        if (elementsArray[i] == element) {
            for (int j = i; j < elementCount - 1; ++j){
                elementsArray[j] = elementsArray[j+1];
                iterationCount++;
            }
            --elementCount;
            elementSet.erase(element);
            break;
        }
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("remove", iterationCount, execTime);
}

void BinarySearchShip::generateElements(){
    int elements = 0;
    while(elements < NUM_OF_ELEMENTS){
      int value = generateRandom(0,MAX_NUM_ELEMENTS);
      if(elementSet.find(value) == elementSet.end()){
        insert(value);
        elements ++;
      }
    }
  }