#ifndef REDBLACKTREESHIP_H
#define REDBLACKTREESHIP_H

#include "Ship.h"
#include <map>

class RedBlackTreeShip : public Ship {
private:
    std::map<int, int> rbtree;

public:
    RedBlackTreeShip();

    int search(int target) override;
    void insert(int element) override;
    void remove(int element) override;
};

#endif
