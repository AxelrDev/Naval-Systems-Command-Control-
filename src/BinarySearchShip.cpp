#include "BinarySearchShip.h"
#include <chrono>
#include <algorithm>
#include <cstdlib>

BinarySearchShip::BinarySearchShip() : Ship("BinarySearch", /*price=*/110) {
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = rand() % 1000;
        sortedArray.push_back(val);
        elementSet.insert(val);
    }
    sortArray();
}

int BinarySearchShip::search(int target) {
    int iterations = 0;
    auto start = std::chrono::high_resolution_clock::now();

    int left = 0, right = sortedArray.size() - 1;
    while (left <= right) {
        ++iterations;
        int mid = (left + right) / 2;
        if (sortedArray[mid] == target) break;
        if (sortedArray[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void BinarySearchShip::insert(int element) {
    sortedArray.push_back(element);
    elementSet.insert(element);
    sortArray();
}

void BinarySearchShip::remove(int element) {
    sortedArray.erase(std::remove(sortedArray.begin(), sortedArray.end(), element), sortedArray.end());
    elementSet.erase(element);
}

void BinarySearchShip::sortArray() {
    std::sort(sortedArray.begin(), sortedArray.end());
}
