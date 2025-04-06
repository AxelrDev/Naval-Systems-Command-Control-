#include "RedBlackTreeShip.h"
#include <chrono>

RedBlackTreeShip::RedBlackTreeShip() : Ship("RedBlackTree", /*price=*/150), root(nullptr) {
    // Insert random elements into the tree and set
}

int RedBlackTreeShip::search(int target) {
    int iterations = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* current = root;
    while (current) {
        iterations++;
        if (target == current->key) break;
        current = (target < current->key) ? current->left : current->right;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void RedBlackTreeShip::insert(int element) {
    Node* inserted = insertNode(element);
    if (inserted) insertFixup(inserted);
    elementSet.insert(element);
}

void RedBlackTreeShip::remove(int element) {
    Node* node = searchNode(element);
    if (node) {
        deleteNode(node);
        elementSet.erase(element);
    }
}

// --- Implementación interna básica de funciones (vacías de momento) ---

RedBlackTreeShip::Node* RedBlackTreeShip::insertNode(int key) {
    // Implementación del RBTree insert
    return nullptr;
}

void RedBlackTreeShip::insertFixup(Node* z) { }

RedBlackTreeShip::Node* RedBlackTreeShip::searchNode(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) return current;
        current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

void RedBlackTreeShip::rotateLeft(Node* x) { }
void RedBlackTreeShip::rotateRight(Node* y) { }

void RedBlackTreeShip::transplant(Node* u, Node* v) { }
RedBlackTreeShip::Node* RedBlackTreeShip::deleteNode(Node* z) { return nullptr; }
void RedBlackTreeShip::deleteFixup(Node* x) { }
