#include "RedBlackTreeShip.h"
#include "Constants.h"
#include <chrono>
#include <cstdlib>

// Constructor: llena aleatoriamente
RedBlackTreeShip::RedBlackTreeShip()
  : Ship("RedBlackTree", PRICE_REDBLACK_TREE),
    rootNode(nullptr)
{
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        insert(rand() % 1000);
    }
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
        current = (target < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void RedBlackTreeShip::insert(int element) {
    if (elementSet.count(element)) return;
    Node* newNode = insertNode(element);
    if (newNode) fixInsertion(newNode);
    if (rootNode) rootNode->isRed = false;
    elementSet.insert(element);
}

void RedBlackTreeShip::remove(int element) {
    Node* z = searchNode(element);
    if (!z) return;
    deleteNode(z);
    elementSet.erase(element);
}

RedBlackTreeShip::Node* RedBlackTreeShip::insertNode(int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = rootNode;
    while (x) {
        y = x;
        x = (z->key < x->key) ? x->leftChild : x->rightChild;
    }
    z->parentNode = y;
    if (!y)       rootNode = z;
    else if (z->key < y->key) y->leftChild  = z;
    else                       y->rightChild = z;
    return z;
}

void RedBlackTreeShip::fixInsertion(Node* z) {
    while (z->parentNode && z->parentNode->isRed) {
        Node* p = z->parentNode;
        Node* g = p->parentNode;
        if (p == g->leftChild) {
            Node* y = g->rightChild;
            if (y && y->isRed) {
                p->isRed = false; y->isRed = false; g->isRed = true;
                z = g;
            } else {
                if (z == p->rightChild) {
                    z = p;
                    rotateLeft(z);
                }
                p->isRed = false;
                g->isRed = true;
                rotateRight(g);
            }
        } else {
            Node* y = g->leftChild;
            if (y && y->isRed) {
                p->isRed = false; y->isRed = false; g->isRed = true;
                z = g;
            } else {
                if (z == p->leftChild) {
                    z = p;
                    rotateRight(z);
                }
                p->isRed = false;
                g->isRed = true;
                rotateLeft(g);
            }
        }
    }
    rootNode->isRed = false;
}

void RedBlackTreeShip::rotateLeft(Node* x) {
    Node* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parentNode = x;
    y->parentNode = x->parentNode;
    if (!x->parentNode)           rootNode = y;
    else if (x == x->parentNode->leftChild)  x->parentNode->leftChild  = y;
    else                                      x->parentNode->rightChild = y;
    y->leftChild = x;
    x->parentNode = y;
}

void RedBlackTreeShip::rotateRight(Node* y) {
    Node* x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parentNode = y;
    x->parentNode = y->parentNode;
    if (!y->parentNode)           rootNode = x;
    else if (y == y->parentNode->rightChild) y->parentNode->rightChild = x;
    else                                      y->parentNode->leftChild  = x;
    x->rightChild = y;
    y->parentNode = x;
}

RedBlackTreeShip::Node* RedBlackTreeShip::searchNode(int key) {
    Node* current = rootNode;
    while (current && current->key != key) {
        current = (key < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    return current;
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

void RedBlackTreeShip::deleteNode(Node* z) {
    Node* y = z;
    bool yOriginalRed = y->isRed;
    Node* x = nullptr;

    if (!z->leftChild) {
        x = z->rightChild;
        transplant(z, z->rightChild);
    } else if (!z->rightChild) {
        x = z->leftChild;
        transplant(z, z->leftChild);
    } else {
        y = treeMinimum(z->rightChild);
        yOriginalRed = y->isRed;
        x = y->rightChild;
        if (y->parentNode == z) {
            if (x) x->parentNode = y;
        } else {
            transplant(y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parentNode = y;
        }
        transplant(z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parentNode = y;
        y->isRed = z->isRed;
    }
    delete z;
    if (!yOriginalRed) {
        fixDeletion(x);
    }
}

void RedBlackTreeShip::fixDeletion(Node* x) {
    while (x != rootNode && (!x || !x->isRed)) {
        Node* p = x ? x->parentNode : nullptr;
        if (p && x == p->leftChild) {
            Node* w = p->rightChild;
            if (w && w->isRed) {
                w->isRed = false;
                p->isRed = true;
                rotateLeft(p);
                w = p->rightChild;
            }
            if (w && (!w->leftChild || !w->leftChild->isRed)
                  && (!w->rightChild || !w->rightChild->isRed)) {
                w->isRed = true;
                x = p;
            } else {
                if (w && (!w->rightChild || !w->rightChild->isRed)) {
                    if (w->leftChild) w->leftChild->isRed = false;
                    w->isRed = true;
                    rotateRight(w);
                    w = p->rightChild;
                }
                if (w) w->isRed = p->isRed;
                p->isRed = false;
                if (w && w->rightChild) w->rightChild->isRed = false;
                rotateLeft(p);
                x = rootNode;
            }
        } else {
            if (!p) break;
            Node* w = p->leftChild;
            if (w && w->isRed) {
                w->isRed = false;
                p->isRed = true;
                rotateRight(p);
                w = p->leftChild;
            }
            if (w && (!w->rightChild || !w->rightChild->isRed)
                  && (!w->leftChild || !w->leftChild->isRed)) {
                w->isRed = true;
                x = p;
            } else {
                if (w && (!w->leftChild || !w->leftChild->isRed)) {
                    if (w->rightChild) w->rightChild->isRed = false;
                    w->isRed = true;
                    rotateLeft(w);
                    w = p->leftChild;
                }
                if (w) w->isRed = p->isRed;
                p->isRed = false;
                if (w && w->leftChild) w->leftChild->isRed = false;
                rotateRight(p);
                x = rootNode;
            }
        }
    }
    if (x) x->isRed = false;
}
