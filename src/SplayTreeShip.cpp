#include "SplayTreeShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

SplayTreeShip::SplayTreeShip()
  : Ship("SplayTree", PRICE_SPLAY_TREE), rootNode(nullptr)
{
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i)
        insert(rand() % 1000);
}

int SplayTreeShip::search(int target) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    Node* found = searchNode(target);
    if (found) {
        splayNode(found);
        ++iterationCount;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void SplayTreeShip::insert(int element) {
    if (elementSet.count(element)) return;
    Node* newNode = insertNode(element);
    if (newNode) {
        splayNode(newNode);
        elementSet.insert(element);
    }
}

void SplayTreeShip::remove(int element) {
    Node* found = searchNode(element);
    if (!found) return;
    splayNode(found);

    Node* leftSub  = found->leftChild;
    Node* rightSub = found->rightChild;
    if (leftSub)  leftSub->parentNode  = nullptr;
    if (rightSub) rightSub->parentNode = nullptr;
    delete found;

    rootNode = joinTrees(leftSub, rightSub);
    elementSet.erase(element);
}

void SplayTreeShip::rotateLeft(Node* x) {
    Node* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parentNode = x;
    y->parentNode = x->parentNode;
    if (!x->parentNode)             rootNode = y;
    else if (x == x->parentNode->leftChild) x->parentNode->leftChild  = y;
    else                                    x->parentNode->rightChild = y;
    y->leftChild = x;
    x->parentNode = y;
}

void SplayTreeShip::rotateRight(Node* y) {
    Node* x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parentNode = y;
    x->parentNode = y->parentNode;
    if (!y->parentNode)             rootNode = x;
    else if (y == y->parentNode->rightChild) y->parentNode->rightChild = x;
    else                                     y->parentNode->leftChild  = x;
    x->rightChild = y;
    y->parentNode = x;
}

void SplayTreeShip::splayNode(Node* x) {
    while (x->parentNode) {
        if (!x->parentNode->parentNode) {
            if (x->parentNode->leftChild == x) rotateRight(x->parentNode);
            else                               rotateLeft(x->parentNode);
        } else if (x->parentNode->leftChild == x
                && x->parentNode->parentNode->leftChild == x->parentNode) {
            rotateRight(x->parentNode->parentNode);
            rotateRight(x->parentNode);
        } else if (x->parentNode->rightChild == x
                && x->parentNode->parentNode->rightChild == x->parentNode) {
            rotateLeft(x->parentNode->parentNode);
            rotateLeft(x->parentNode);
        } else if (x->parentNode->leftChild == x
                && x->parentNode->parentNode->rightChild == x->parentNode) {
            rotateRight(x->parentNode);
            rotateLeft(x->parentNode);
        } else {
            rotateLeft(x->parentNode);
            rotateRight(x->parentNode);
        }
    }
}

SplayTreeShip::Node* SplayTreeShip::searchNode(int key) {
    Node* current = rootNode;
    while (current) {
        if (current->key == key) return current;
        current = (key < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    return nullptr;
}

SplayTreeShip::Node* SplayTreeShip::insertNode(int key) {
    Node* newNode = new Node(key);
    Node* parent  = nullptr;
    Node* current = rootNode;
    while (current) {
        parent  = current;
        current = (newNode->key < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    newNode->parentNode = parent;
    if (!parent)               rootNode = newNode;
    else if (newNode->key < parent->key) parent->leftChild  = newNode;
    else                                  parent->rightChild = newNode;
    return newNode;
}

SplayTreeShip::Node* SplayTreeShip::joinTrees(Node* leftTree, Node* rightTree) {
    if (!leftTree)  return rightTree;
    if (!rightTree) return leftTree;
    Node* maxNode = leftTree;
    while (maxNode->rightChild) maxNode = maxNode->rightChild;
    splayNode(maxNode);
    maxNode->rightChild    = rightTree;
    rightTree->parentNode  = maxNode;
    return maxNode;
}
