#ifndef REDBLACKTREESHIP_H
#define REDBLACKTREESHIP_H

#include "Ship.h"

class RedBlackTreeShip : public Ship {
private:
    struct Node {
        int key;
        bool red;
        Node* left;
        Node* right;
        Node* parent;

        Node(int k) : key(k), red(true), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void insertFixup(Node* z);
    Node* insertNode(int key);
    Node* searchNode(int key);

public:
    RedBlackTreeShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // REDBLACKTREESHIP_H
