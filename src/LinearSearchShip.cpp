#include "LinearSearchShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

LinearSearchShip::LinearSearchShip()
  : Ship("LinearSearch", PRICE_LINEAR_SEARCH), headNode(nullptr)
{
    generateElements();
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
    int iterationCount = 1;
    auto start = std::chrono::high_resolution_clock::now();
    
    Node* newNode = new Node(element);
    newNode->nextNode = headNode;
    headNode = newNode;
    elementSet.insert(element);

    auto end = std::chrono::high_resolution_clock::now();
    logOperation("insert", iterationCount,
                 std::chrono::duration<double>(end-start).count());
}

void LinearSearchShip::remove(int element) {
    int iterationCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* current = headNode;
    Node* previous = nullptr;

    while (current) {
        ++iterationCount;
        if (current->nodeValue == element) break;
        previous = current;
        current = current->nextNode;
    }

    if (current) {
        // Element found
        if (!previous) {
            headNode = current->nextNode;
        } else {
            previous->nextNode = current->nextNode;
        }
        delete current;
        elementSet.erase(element);
    }

    auto end = std::chrono::high_resolution_clock::now();
    logOperation("remove", iterationCount,
                 std::chrono::duration<double>(end-start).count());
}

void LinearSearchShip::generateElements(){
  int elements = 0;
  while(elements < NUM_OF_ELEMENTS){
    int value = generateRandom(0,1000);
    if(elementSet.find(value) == elementSet.end()){
      insert(value);
      elements ++;
    }
  }
}