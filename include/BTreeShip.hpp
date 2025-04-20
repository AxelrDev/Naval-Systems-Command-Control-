#ifndef BTREE_SHIP_HPP
#define BTREE_SHIP_HPP

#include "Ship.hpp"
#include "Constants.hpp"   //  NUM_OF_ELEMENTS, PRICE_BTREE (defínelo)
#include <vector>
#include <set>
#include <chrono>

#define MAX_KEYS 5          // (2 * MIN_KEYS)
#define MIN_KEYS 3

class BTreeShip : public Ship
{
private:
    /* -----------------------------------------------------------
     *   NODO B‑tree (índices 1 … count, enlaces 0 … count)
     * ----------------------------------------------------------- */
    struct Node {
        int  key[MAX_KEYS + 1]{};
        int  count{0};
        Node* child[MAX_KEYS + 2]{};   // +2 para evitar overrun en splits
    };

    Node* rootNode{nullptr};

    /* -- helpers -- */
    Node* createNode(int key, Node* child0, Node* child1);
    void  destroy   (Node* n);

    /* inserción */
    bool  insertRec (int key, Node* cur,
                     int& upKey, Node*& newChild,int &iterationCount );

    void  addKeyToNode(int key, Node* child,
                       Node* target, int pos, int &iterationCount);

    void  splitNode (int key, Node* child, Node* cur,
                     int  pos,  int& upKey, Node*& newChild, int &iterationCount);

    /* eliminación */
    bool  removeRec  (int key, Node* cur, int &iterationCount);
    void  fixUnderflow(Node* cur, int pos, int &iterationCount);
    void shiftLeft(Node* parent, int pos, int& iterationCount);
    void shiftRight(Node* parent, int pos, int& iterationCount);
    void merge(Node* parent, int pos, int& iterationCount);
    int   getPred    (Node* cur, int& iterationCount);

    /* búsqueda */
    void  searchRec  (int key, Node* cur,
                      int& iterations) const;

public:
    BTreeShip();
    ~BTreeShip() override;

    /* interface Ship */
    int  search (int key)      override;
    void insert (int key)      override;
    void remove (int key)      override;
};

#endif  // BTREE_SHIP_HPP
