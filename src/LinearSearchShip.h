#ifndef LINEARSEARCHSHIP_H
#define LINEARSEARCHSHIP_H

#include "Ship.h"

class LinearSearchShip : public Ship {
private:
    struct Node {
        int   nodeValue;
        Node* nextNode;
        Node(int v) : nodeValue(v), nextNode(nullptr) {}
    };
    Node* headNode;

public:
    LinearSearchShip();
    ~LinearSearchShip();

    int  search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif // LINEARSEARCHSHIP_H
