#ifndef SPLAYTREESHIP_H
#define SPLAYTREESHIP_H

#include "Ship.h"

class SplayTreeShip : public Ship {
private:
    struct Node {
        int   key;
        Node* leftChild;
        Node* rightChild;
        Node* parentNode;
        Node(int k)
          : key(k),
            leftChild(nullptr), rightChild(nullptr), parentNode(nullptr)
        {}
    };
    Node* rootNode;

    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void splayNode(Node* x);
    Node* insertNode(int key);
    Node* searchNode(int key);
    Node* joinTrees(Node* leftTree, Node* rightTree);

public:
    SplayTreeShip();
    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // SPLAYTREESHIP_H
