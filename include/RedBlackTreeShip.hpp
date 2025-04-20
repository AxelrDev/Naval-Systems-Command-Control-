#ifndef REDBLACKTREESHIP_HPP
#define REDBLACKTREESHIP_HPP

#include "Ship.hpp"

class RedBlackTreeShip : public Ship {
private:
struct Node {
    int    key;
    bool   isRed;
    Node*  parentNode;
    Node*  leftChild;
    Node*  rightChild;

    Node(int k)
      : key(k)
      , isRed(true)
      , parentNode(nullptr)
      , leftChild(nullptr)
      , rightChild(nullptr)
    {}
};
    Node* rootNode;

    // Rotaciones
    void rotateLeft(Node* x);
    void rotateRight(Node* y);

    // Inserción
    void  fixInsertion(Node* z, int &iterationCount);
    Node* insertNode(int key, int &iterationCount);

    // Búsqueda interna
    Node* searchNode(int key, int &iterationCount);

    // Eliminación
    void transplant(Node* u, Node* v);
    Node* treeMinimum(Node* x);
    void  fixDeletion (Node* x, int &iterationCount);
    void  deleteNode(Node* z, int &iterationCount);
    void deleteSubtree(Node* node);

public:
    RedBlackTreeShip();
    ~RedBlackTreeShip() override;

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // REDBLACKTREESHIP_HPP