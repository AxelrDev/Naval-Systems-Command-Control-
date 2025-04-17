#ifndef REDBLACKTREESHIP_H
#define REDBLACKTREESHIP_H

#include "Ship.h"

class RedBlackTreeShip : public Ship {
private:
    struct Node {
        int   key;
        bool  isRed;
        Node* leftChild;
        Node* rightChild;
        Node* parentNode;
        Node(int k)
          : key(k), isRed(true),
            leftChild(nullptr), rightChild(nullptr), parentNode(nullptr)
        {}
    };
    Node* rootNode;

    // Rotaciones
    void rotateLeft(Node* x);
    void rotateRight(Node* y);

    // Inserción
    void fixInsertion(Node* z);
    Node* insertNode(int key);

    // Búsqueda interna
    Node* searchNode(int key);

    // Eliminación
    void transplant(Node* u, Node* v);
    Node* treeMinimum(Node* x);
    void fixDeletion(Node* x);
    void deleteNode(Node* z);
    void deleteSubtree(Node* node);

public:
    RedBlackTreeShip();
    ~RedBlackTreeShip() override;

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // REDBLACKTREESHIP_H
