#include "LinearSearchShip.h"
#include "Constants.h"
#include <chrono>
#include <cstdlib>

LinearSearchShip::LinearSearchShip()
  : Ship("LinearSearch", PRICE_LINEAR_SEARCH), headNode(nullptr)
{
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int value = rand() % 1000;
        Node* newNode = new Node(value);
        newNode->nextNode = headNode;
        headNode = newNode;
        elementSet.insert(value);
    }
}

LinearSearchShip::~LinearSearchShip() {
    Node* current = headNode;
    while (current) {
        Node* toDelete = current;
        current = current->nextNode;
        delete toDelete;
    }
}

int LinearSearchShip::search(int target) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    for (Node* current = headNode; current; current = current->nextNode) {
        ++iterationCount;
        if (current->nodeValue == target) break;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void LinearSearchShip::insert(int element) {
    Node* newNode = new Node(element);
    newNode->nextNode = headNode;
    headNode = newNode;
    elementSet.insert(element);
}

void LinearSearchShip::remove(int element) {
    Node* current = headNode;
    Node* previous = nullptr;
    while (current && current->nodeValue != element) {
        previous = current;
        current = current->nextNode;
    }
    if (!current) return;
    if (!previous) headNode = current->nextNode;
    else            previous->nextNode = current->nextNode;
    delete current;
    elementSet.erase(element);
}
