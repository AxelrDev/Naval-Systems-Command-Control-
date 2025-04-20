#ifndef SPLAYTREESHIP_HPP
#define SPLAYTREESHIP_HPP

#include "Ship.hpp"

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
    void  splayNode(Node* node, int &iterationCount);
    Node* insertNode(int key, int &iterationCount);
    Node* searchNode(int key, int &iterationCount);
    Node* joinTrees(Node* leftTree, Node* rightTree, int &iterationCount);

public:
    SplayTreeShip();
    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // SPLAYTREESHIP_H
