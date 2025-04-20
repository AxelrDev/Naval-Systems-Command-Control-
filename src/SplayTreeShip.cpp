#include "SplayTreeShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

SplayTreeShip::SplayTreeShip()
  : Ship("SplayTree", PRICE_SPLAY_TREE), rootNode(nullptr)
{
    generateElements();
}

int SplayTreeShip::search(int target) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    Node* foundNode = searchNode(target, iterationCount);
    if (foundNode) {
        splayNode(foundNode, iterationCount);
        ++iterationCount;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double executionTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, executionTime);
    return iterationCount;
}

void SplayTreeShip::insert(int element) {
    if (elementSet.count(element)) return;
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    Node* newNode = insertNode(element, iterationCount);
    if (newNode) {
        splayNode(newNode, iterationCount);
        elementSet.insert(element);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double executionTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("insert", iterationCount, executionTime);
}

void SplayTreeShip::remove(int element) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    Node* targetNode = searchNode(element, iterationCount);
    if (targetNode) {
        splayNode(targetNode, iterationCount);
        ++iterationCount;
        Node* leftSubtree  = targetNode->leftChild;
        Node* rightSubtree = targetNode->rightChild;
        if (leftSubtree)  leftSubtree->parentNode  = nullptr;
        if (rightSubtree) rightSubtree->parentNode = nullptr;
        delete targetNode;

        rootNode = joinTrees(leftSubtree, rightSubtree, iterationCount);
        elementSet.erase(element);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double executionTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("remove", iterationCount, executionTime);
}

void SplayTreeShip::rotateLeft(Node* pivotNode) {
    Node* childNode = pivotNode->rightChild;
    pivotNode->rightChild = childNode->leftChild;
    if (childNode->leftChild)
        childNode->leftChild->parentNode = pivotNode;
    childNode->parentNode = pivotNode->parentNode;
    if (!pivotNode->parentNode)
        rootNode = childNode;
    else if (pivotNode == pivotNode->parentNode->leftChild)
        pivotNode->parentNode->leftChild = childNode;
    else
        pivotNode->parentNode->rightChild = childNode;
    childNode->leftChild = pivotNode;
    pivotNode->parentNode = childNode;
}

void SplayTreeShip::rotateRight(Node* pivotNode) {
    Node* childNode = pivotNode->leftChild;
    pivotNode->leftChild = childNode->rightChild;
    if (childNode->rightChild)
        childNode->rightChild->parentNode = pivotNode;
    childNode->parentNode = pivotNode->parentNode;
    if (!pivotNode->parentNode)
        rootNode = childNode;
    else if (pivotNode == pivotNode->parentNode->rightChild)
        pivotNode->parentNode->rightChild = childNode;
    else
        pivotNode->parentNode->leftChild = childNode;
    childNode->rightChild = pivotNode;
    pivotNode->parentNode = childNode;
}

void SplayTreeShip::splayNode(Node* node, int &iterationCount) {
    while (node->parentNode) {
        ++iterationCount;
        Node* parentNode    = node->parentNode;
        Node* grandParent   = parentNode->parentNode;
        // Zig step
        if (!grandParent) {
            if (node == parentNode->leftChild)
                rotateRight(parentNode);
            else
                rotateLeft(parentNode);
        }
        // Zig-Zig step
        else if (node == parentNode->leftChild
              && parentNode == grandParent->leftChild) {
            rotateRight(grandParent);
            rotateRight(parentNode);
        }
        else if (node == parentNode->rightChild
              && parentNode == grandParent->rightChild) {
            rotateLeft(grandParent);
            rotateLeft(parentNode);
        }
        // Zig-Zag step
        else if (node == parentNode->leftChild
              && parentNode == grandParent->rightChild) {
            rotateRight(parentNode);
            rotateLeft(grandParent);
        }
        else {
            rotateLeft(parentNode);
            rotateRight(grandParent);
        }
    }
}

SplayTreeShip::Node* SplayTreeShip::searchNode(int key, int &iterationCount) {
    Node* currentNode = rootNode;
    while (currentNode) {
        ++iterationCount;
        if (currentNode->key == key)
            return currentNode;
        currentNode = (key < currentNode->key)
                      ? currentNode->leftChild
                      : currentNode->rightChild;
    }
    return nullptr;
}

SplayTreeShip::Node* SplayTreeShip::insertNode(int key, int &iterationCount) {
    Node* newNode    = new Node(key);
    Node* parentNode = nullptr;
    Node* currentNode= rootNode;
    while (currentNode) {
        ++iterationCount;
        parentNode = currentNode;
        currentNode= (key < currentNode->key)
                      ? currentNode->leftChild
                      : currentNode->rightChild;
    }
    newNode->parentNode = parentNode;
    if (!parentNode)
        rootNode = newNode;
    else if (key < parentNode->key)
        parentNode->leftChild  = newNode;
    else
        parentNode->rightChild = newNode;
    return newNode;
}

SplayTreeShip::Node* SplayTreeShip::joinTrees(Node* leftTree, Node* rightTree, int &iterationCount) {
    if (!leftTree)  return rightTree;
    if (!rightTree) return leftTree;
    Node* maxNode = leftTree;
    while (maxNode->rightChild) {
        ++iterationCount;
        maxNode = maxNode->rightChild;
    }
    splayNode(maxNode, iterationCount);
    ++iterationCount;
    maxNode->rightChild    = rightTree;
    rightTree->parentNode  = maxNode;
    return maxNode;
}
