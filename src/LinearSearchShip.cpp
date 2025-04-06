#include "LinearSearchShip.h"
#include <chrono>
#include <cstdlib>

LinearSearchShip::LinearSearchShip() : Ship("LinearSearch", /*price=*/100) {
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = rand() % 1000;
        linkedList.push_back(val);
        elementSet.insert(val);
    }
}

int LinearSearchShip::search(int target) {
    int iterations = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int val : linkedList) {
        ++iterations;
        if (val == target) break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void LinearSearchShip::insert(int element) {
    linkedList.push_back(element);
    elementSet.insert(element);
}

void LinearSearchShip::remove(int element) {
    linkedList.remove(element);
    elementSet.erase(element);
}
