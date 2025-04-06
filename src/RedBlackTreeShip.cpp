#include "RedBlackTreeShip.h"
#include <chrono>
#include <cstdlib>

RedBlackTreeShip::RedBlackTreeShip() : Ship("RedBlackTree", /*price=*/150), root(nullptr) {
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = rand() % 1000;
        insert(val);
    }
}

int RedBlackTreeShip::search(int target) {
    int iterations = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* current = root;
    while (current) {
        ++iterations;
        if (target == current->key) break;
        current = (target < current->key) ? current->left : current->right;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();
    logOperation("search", iterations, time);
    return iterations;
}

void RedBlackTreeShip::insert(int element) {
    if (elementSet.count(element)) return;
    Node* inserted = insertNode(element);
    if (inserted) insertFixup(inserted);
    root->red = false; // Root is always black
    elementSet.insert(element);
}

void RedBlackTreeShip::remove(int element) {
    // Eliminación no implementada por simplicidad.
    elementSet.erase(element);
}

RedBlackTreeShip::Node* RedBlackTreeShip::insertNode(int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    return z;
}

void RedBlackTreeShip::insertFixup(Node* z) {
    while (z->parent && z->parent->red) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                rotateRight(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->red = false;
}

void RedBlackTreeShip::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTreeShip::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

RedBlackTreeShip::Node* RedBlackTreeShip::searchNode(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key)
            return current;
        current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}
