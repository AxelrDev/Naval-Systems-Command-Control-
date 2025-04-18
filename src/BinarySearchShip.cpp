#include "BinarySearchShip.h"
#include "Constants.h"
#include <chrono>
#include <cstdlib>

BinarySearchShip::BinarySearchShip()
  : Ship("BinarySearch", PRICE_BINARY_SEARCH),
    elementCount(0), maxCapacity(MAX_NUM_ELEMENTS)
{
    elementsArray = new int[maxCapacity];
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int value = rand() % 1000;
        elementsArray[elementCount++] = value;
        elementSet.insert(value);
    }
    sortArray();
}

BinarySearchShip::~BinarySearchShip() {
    delete[] elementsArray;
}

void BinarySearchShip::sortArray() {
    for (int i = 1; i < elementCount; ++i) {
        int keyValue = elementsArray[i];
        int j = i - 1;
        while (j >= 0 && elementsArray[j] > keyValue) {
            elementsArray[j+1] = elementsArray[j];
            --j;
        }
        elementsArray[j+1] = keyValue;
    }
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
    elementsArray[elementCount++] = element;
    elementSet.insert(element);
    sortArray();
}

void BinarySearchShip::remove(int element) {
    for (int i = 0; i < elementCount; ++i) {
        if (elementsArray[i] == element) {
            for (int j = i; j < elementCount - 1; ++j)
                elementsArray[j] = elementsArray[j+1];
            --elementCount;
            elementSet.erase(element);
            break;
        }
    }
}
