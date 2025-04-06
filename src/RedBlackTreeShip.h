#ifndef REDBLACKTREESHIP_H
#define REDBLACKTREESHIP_H

#include "Ship.h"
#include <map>

class RedBlackTreeShip : public Ship {
private:
    struct Node {
        int key;
        bool red; // true = red, false = black
        Node* left;
        Node* right;
        Node* parent;
    };
    
    Node* root;

    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void insertFixup(Node* z);
    Node* insertNode(int key);
    Node* searchNode(int key);
    Node* minimum(Node* node);
    void transplant(Node* u, Node* v);
    Node* deleteNode(Node* z);
    void deleteFixup(Node* x);

public:
    RedBlackTreeShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // REDBLACKTREESHIP_H
