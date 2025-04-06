#include "SetShip.h"
#include <chrono>
#include <cstdlib>

SetShip::SetShip() : Ship("Set", /*price=*/120) {
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = rand() % 1000;
        internalSet.insert(val);
        elementSet.insert(val);
    }
}

int SetShip::search(int target) {
    int iterations = 1; // std::set has log(n) time but we abstract that as 1 iteration
    auto start = std::chrono::high_resolution_clock::now();

    internalSet.find(target); // No need to check result for simulation

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void SetShip::insert(int element) {
    internalSet.insert(element);
    elementSet.insert(element);
}

void SetShip::remove(int element) {
    internalSet.erase(element);
    elementSet.erase(element);
}
