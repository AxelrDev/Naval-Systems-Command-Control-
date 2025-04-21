#include "RedBlackTreeShip.hpp"
#include "Constants.hpp"
#include <chrono>
#include <cstdlib>

// Constructor: llena aleatoriamente
RedBlackTreeShip::RedBlackTreeShip()
  : Ship("RedBlackTree", PRICE_REDBLACK_TREE),
    rootNode(nullptr)
{
  generateElements();
}


RedBlackTreeShip::~RedBlackTreeShip() {
    deleteSubtree(rootNode);
}

void RedBlackTreeShip::deleteSubtree(Node* node) {
    if (!node) return;
    deleteSubtree(node->leftChild);
    deleteSubtree(node->rightChild);
    delete node;
}

int RedBlackTreeShip::search(int target) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    Node* current = rootNode;
    while (current) {
        ++iterationCount;
        if (target == current->key) break;
        current = (target < current->key) ? current->leftChild : current->rightChild;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void RedBlackTreeShip::insert(int element) {
    if (elementSet.count(element)) return;

    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    // walk down the tree, counting each comparison/step
    Node* newNode = insertNode(element, iterationCount);
    if (newNode) fixInsertion(newNode, iterationCount);

    if (rootNode) rootNode->isRed = false;
    elementSet.insert(element);

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("insert", iterationCount, execTime);
}

void RedBlackTreeShip::remove(int element) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    Node* z = searchNode(element, iterationCount);
    if (z) {
        deleteNode(z, iterationCount);
        elementSet.erase(element);
    }
    // even if not found, you’ll still log “remove” with the cost of the failed search

    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("remove", iterationCount, execTime);
}

RedBlackTreeShip::Node* RedBlackTreeShip::insertNode(int key, int &iterationCount) {
    Node* newNode = new Node(key);
    Node* parentNode = nullptr;
    Node* currentNode = rootNode;
    while (currentNode) {
        ++iterationCount;
        parentNode = currentNode;
        currentNode = (key < currentNode->key)
                      ? currentNode->leftChild
                      : currentNode->rightChild;
    }
    newNode->parentNode = parentNode;
    if (!parentNode){
        rootNode = newNode;
        ++iterationCount;
    }
    else if (key < parentNode->key)
        parentNode->leftChild = newNode;
    else
        parentNode->rightChild = newNode;
    return newNode;
}

void RedBlackTreeShip::fixInsertion(Node* node, int &iterationCount) {
    while (node->parentNode && node->parentNode->isRed
           && node->parentNode->parentNode) {
        ++iterationCount;
        Node* parentNode = node->parentNode;
        Node* grandParent = parentNode->parentNode;
        if (parentNode == grandParent->leftChild) {
            Node* uncle = grandParent->rightChild;
            if (uncle && uncle->isRed) {
                ++iterationCount;
                parentNode->isRed = false;
                uncle->isRed = false;
                grandParent->isRed = true;
                node = grandParent;
            } else {
                if (node == parentNode->rightChild) {
                    ++iterationCount;
                    rotateLeft(parentNode);
                    node = parentNode;
                }
                ++iterationCount;
                parentNode->isRed = false;
                grandParent->isRed = true;
                rotateRight(grandParent);
            }
        } else {
            Node* uncle = grandParent->leftChild;
            if (uncle && uncle->isRed) {
                ++iterationCount;
                parentNode->isRed = false;
                uncle->isRed = false;
                grandParent->isRed = true;
                node = grandParent;
            } else {
                if (node == parentNode->leftChild) {
                    ++iterationCount;
                    rotateRight(parentNode);
                    node = parentNode;
                }
                ++iterationCount;
                parentNode->isRed = false;
                grandParent->isRed = true;
                rotateLeft(grandParent);
            }
        }
    }
    if (rootNode)
        rootNode->isRed = false;
}


void RedBlackTreeShip::rotateLeft(Node* x) {
    // Evita hacer y = x->rightChild cuando ese hijo no exista
    if (!x || !x->rightChild) return;

    Node* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parentNode = x;
    y->parentNode = x->parentNode;
    if (!x->parentNode)                rootNode = y;
    else if (x == x->parentNode->leftChild)  x->parentNode->leftChild  = y;
    else                                     x->parentNode->rightChild = y;
    y->leftChild  = x;
    x->parentNode = y;
}

void RedBlackTreeShip::rotateRight(Node* y) {
    // Evita hacer x = y->leftChild cuando ese hijo no exista
    if (!y || !y->leftChild) return;

    Node* x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parentNode = y;
    x->parentNode = y->parentNode;
    if (!y->parentNode)                rootNode = x;
    else if (y == y->parentNode->rightChild) y->parentNode->rightChild = x;
    else                                    y->parentNode->leftChild  = x;
    x->rightChild = y;
    y->parentNode = x;
}

RedBlackTreeShip::Node* RedBlackTreeShip::searchNode(int key, int &iterationCount) {
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

void RedBlackTreeShip::transplant(Node* u, Node* v) {
    if (!u->parentNode)        rootNode = v;
    else if (u == u->parentNode->leftChild)  u->parentNode->leftChild  = v;
    else                                     u->parentNode->rightChild = v;
    if (v) v->parentNode = u->parentNode;
}

RedBlackTreeShip::Node* RedBlackTreeShip::treeMinimum(Node* x) {
    while (x->leftChild) x = x->leftChild;
    return x;
}

void RedBlackTreeShip::deleteNode(Node* node, int &iterationCount) {
    ++iterationCount;
    Node* y = node;
    bool originalColor = y->isRed;
    Node* x = nullptr;

    if (!node->leftChild) {
        ++iterationCount;
        x = node->rightChild;
        transplant(node, node->rightChild);
    } else if (!node->rightChild) {
        ++iterationCount;
        x = node->leftChild;
        transplant(node, node->leftChild);
    } else {
        ++iterationCount;
        y = treeMinimum(node->rightChild);
        originalColor = y->isRed;
        x = y->rightChild;
        if (y->parentNode != node) {
            transplant(y, y->rightChild);
            y->rightChild = node->rightChild;
            y->rightChild->parentNode = y;
        }
        transplant(node, y);
        y->leftChild = node->leftChild;
        y->leftChild->parentNode = y;
        y->isRed = node->isRed;
    }
    delete node;
    if (!originalColor)
        fixDeletion(x, iterationCount);
}

void RedBlackTreeShip::fixDeletion(Node* node, int &iterationCount) {
    while (node != rootNode && (!node || !node->isRed)) {
        ++iterationCount;
        Node* parentNode = node ? node->parentNode : nullptr;
        if (parentNode && node == parentNode->leftChild) {
            Node* sibling = parentNode->rightChild;
            if (sibling && sibling->isRed) {
                ++iterationCount;
                sibling->isRed = false;
                parentNode->isRed = true;
                rotateLeft(parentNode);
                sibling = parentNode->rightChild;
            }
            if (sibling && (!sibling->leftChild || !sibling->leftChild->isRed)
                        && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                ++iterationCount;
                sibling->isRed = true;
                node = parentNode;
            } else {
                if (sibling && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                    ++iterationCount;
                    if (sibling->leftChild)
                        sibling->leftChild->isRed = false;
                    sibling->isRed = true;
                    rotateRight(sibling);
                    sibling = parentNode->rightChild;
                }
                ++iterationCount;
                if (sibling)
                    sibling->isRed = parentNode->isRed;
                parentNode->isRed = false;
                if (sibling && sibling->rightChild)
                    sibling->rightChild->isRed = false;
                rotateLeft(parentNode);
                node = rootNode;
            }
        } else {
            if (!parentNode) break;
            Node* sibling = parentNode->leftChild;
            if (sibling && sibling->isRed) {
                ++iterationCount;
                sibling->isRed = false;
                parentNode->isRed = true;
                rotateRight(parentNode);
                sibling = parentNode->leftChild;
            }
            if (sibling && (!sibling->leftChild || !sibling->leftChild->isRed)
                        && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                ++iterationCount;
                sibling->isRed = true;
                node = parentNode;
            } else {
                if (sibling && (!sibling->leftChild || !sibling->leftChild->isRed)) {
                    ++iterationCount;
                    if (sibling->rightChild)
                        sibling->rightChild->isRed = false;
                    sibling->isRed = true;
                    rotateLeft(sibling);
                    sibling = parentNode->leftChild;
                }
                ++iterationCount;
                if (sibling)
                    sibling->isRed = parentNode->isRed;
                parentNode->isRed = false;
                if (sibling && sibling->leftChild)
                    sibling->leftChild->isRed = false;
                rotateRight(parentNode);
                node = rootNode;
            }
        }
    }
    if (node)
        node->isRed = false;
}

void RedBlackTreeShip::generateElements(){
    int elements = 0;
    while(elements < NUM_OF_ELEMENTS){
      int value = generateRandom(0,MAX_NUM_ELEMENTS);
      if(elementSet.find(value) == elementSet.end()){
        insert(value);
        elements ++;
      }
    }
  }