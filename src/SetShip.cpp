#include "SetShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

SetShip::SetShip()
  : Ship("Set", PRICE_SET),
    elementCount(0), maxCapacity(MAX_NUM_ELEMENTS)
{
    elementsArray = new int[maxCapacity];
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int value = rand() % 1000;
        insert(value);
    }
}

SetShip::~SetShip() {
    delete[] elementsArray;
}

int SetShip::findIndex(int element) {
    int left = 0, right = elementCount - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if      (elementsArray[mid] == element) return mid;
        else if (elementsArray[mid] < element)  left  = mid + 1;
        else                                     right = mid - 1;
    }
    return -1;
}

int SetShip::search(int target) {
    int iterationCount = 0;
    int left = 0, right = elementCount - 1;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (left <= right) {
        ++iterationCount;
        int mid = (left + right) / 2;
        if      (elementsArray[mid] == target) break;
        else if (elementsArray[mid] < target)  left  = mid + 1;
        else                                    right = mid - 1;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void SetShip::insert(int element) {
    if (findIndex(element) != -1) return;
    int i = elementCount - 1;
    while (i >= 0 && elementsArray[i] > element) {
        elementsArray[i+1] = elementsArray[i];
        --i;
    }
    elementsArray[i+1] = element;
    ++elementCount;
    elementSet.insert(element);
}

void SetShip::remove(int element) {
    int idx = findIndex(element);
    if (idx == -1) return;
    for (int i = idx; i < elementCount - 1; ++i)
        elementsArray[i] = elementsArray[i+1];
    --elementCount;
    elementSet.erase(element);
}
