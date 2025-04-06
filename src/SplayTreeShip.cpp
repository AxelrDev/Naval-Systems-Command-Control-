#include "SplayTreeShip.h"
#include <chrono>

SplayTreeShip::SplayTreeShip() : Ship("SplayTree", /*price=*/160), root(nullptr) {
    // Insert random elements
}

int SplayTreeShip::search(int target) {
    int iterations = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* node = searchNode(target);
    if (node) splay(node);

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void SplayTreeShip::insert(int element) {
    Node* inserted = insertNode(element);
    if (inserted) splay(inserted);
    elementSet.insert(element);
}

void SplayTreeShip::remove(int element) {
    Node* node = searchNode(element);
    if (!node) return;
    splay(node);

    // Eliminar el nodo y reorganizar el árbol
    Node* leftSub = node->left;
    Node* rightSub = node->right;
    if (leftSub) leftSub->parent = nullptr;
    if (rightSub) rightSub->parent = nullptr;
    root = join(leftSub, rightSub);
    delete node;
    elementSet.erase(element);
}

// --- Implementaciones internas básicas ---

void SplayTreeShip::splay(Node* x) { }
void SplayTreeShip::rotateLeft(Node* x) { }
void SplayTreeShip::rotateRight(Node* y) { }

SplayTreeShip::Node* SplayTreeShip::searchNode(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) return current;
        current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

SplayTreeShip::Node* SplayTreeShip::insertNode(int key) {
    // Implementar inserción normal tipo BST
    return nullptr;
}

SplayTreeShip::Node* SplayTreeShip::join(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    Node* maxLeft = left;
    while (maxLeft->right) maxLeft = maxLeft->right;
    splay(maxLeft);
    maxLeft->right = right;
    right->parent = maxLeft;
    return maxLeft;
}
