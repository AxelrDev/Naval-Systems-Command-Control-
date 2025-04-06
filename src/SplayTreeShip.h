#ifndef SPLAYTREESHIP_H
#define SPLAYTREESHIP_H

#include "Ship.h"

class SplayTreeShip : public Ship {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* parent;
    };

    Node* root;

    void splay(Node* node);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    Node* searchNode(int key);
    Node* insertNode(int key);
    Node* deleteNode(Node* key);
    Node* maximum(Node* node);
    Node* join(Node* leftSubtree, Node* rightSubtree);

public:
    SplayTreeShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // SPLAYTREESHIP_H
