#include "BTreeShip.h"
#include <algorithm>
#include <cstdlib>   // rand()
#include <iostream>  // mensajes de depuración opcionales

/* ============================================================
 *   Construcción / destrucción
 * ============================================================ */
BTreeShip::BTreeShip()
    : Ship("BTree", 200)
{
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i)
        insert(std::rand() % 1000);
}

BTreeShip::~BTreeShip() { destroy(rootNode); }

void BTreeShip::destroy(Node* n)
{
    if (!n) return;
    for (int i = 0; i <= n->count; ++i)
        destroy(n->child[i]);
    delete n;
}

/* ============================================================
 *   Utils
 * ============================================================ */
BTreeShip::Node*
BTreeShip::createNode(int key, Node* child0, Node* child1)
{
    Node* n  = new Node;
    n->count = 1;
    n->key[1]   = key;
    n->child[0] = child0;
    n->child[1] = child1;
    return n;
}

void BTreeShip::addKeyToNode(int key, Node* child,
                             Node* target, int pos)
{
    /* abre espacio desde el final hacia 'pos'                       */
    for (int i = target->count; i > pos; --i) {
        target->key  [i + 1] = target->key  [i];
        target->child[i + 1] = target->child[i];
    }
    target->key  [pos + 1] = key;
    target->child[pos + 1] = child;
    ++target->count;
}

/* ============================================================
 *   Inserción recursiva
 * ============================================================ */
bool BTreeShip::insertRec(int key, Node* cur,
                          int& upKey, Node*& newChild)
{
    /* caso hoja */
    if (!cur) { upKey = key; newChild = nullptr; return true; }

    /* encontrar posición */
    int pos;
    for (pos = cur->count;
         pos >= 1 && key < cur->key[pos];
         --pos);

    if (pos >= 1 && key == cur->key[pos]) {
        std::cout << "Valor duplicado no permitido\n";
        return false;
    }

    if (insertRec(key, cur->child[pos], upKey, newChild)) {

        if (cur->count < MAX_KEYS) {          // cabe
            addKeyToNode(upKey, newChild, cur, pos);
            return false;                     // nada que propagar
        }
        /* overflow -> split */
        splitNode(upKey, newChild, cur, pos, upKey, newChild);
        return true;                          // propaga median
    }
    return false;
}

void BTreeShip::splitNode(int key, Node* child, Node* cur,
                          int pos, int& upKey, Node*& newChild)
{
    int mid = (pos > MIN_KEYS) ? MIN_KEYS + 1 : MIN_KEYS;

    /*  nuevo nodo                                                  */
    newChild = new Node;

    /* mover segunda mitad                                          */
    for (int i = mid + 1, j = 1; i <= MAX_KEYS; ++i, ++j) {
        newChild->key  [j] = cur->key  [i];
        newChild->child[j] = cur->child[i];
    }
    newChild->child[0] = cur->child[mid];

    newChild->count = MAX_KEYS - mid;
    cur->count      = mid - 1;          // median queda fuera

    /* inserta clave en el lado adecuado                            */
    if (pos <= MIN_KEYS)
        addKeyToNode(key, child, cur, pos);
    else
        addKeyToNode(key, child, newChild, pos - mid);

    /* mediana que sube                                             */
    upKey = cur->key[mid];
}

void BTreeShip::insert(int key)
{
    if (elementSet.count(key)) return;          // duplicado

    int upKey;
    Node* newChild;
    if (insertRec(key, rootNode, upKey, newChild)) {
        rootNode = createNode(upKey, rootNode, newChild);
    }

    elementSet.insert(key);
}

/* ============================================================
 *   Búsqueda
 * ============================================================ */
void BTreeShip::searchRec(int key, Node* cur,
                          int& iters) const
{
    if (!cur) return;
    ++iters;

    int pos;
    for (pos = 1; pos <= cur->count && key > cur->key[pos]; ++pos);

    if (pos <= cur->count && key == cur->key[pos]) return;

    searchRec(key, cur->child[pos - 1], iters);
}

int BTreeShip::search(int key)
{
    int iterations = 0;
    auto t0 = std::chrono::high_resolution_clock::now();

    searchRec(key, rootNode, iterations);

    auto t1 = std::chrono::high_resolution_clock::now();
    double exec = std::chrono::duration<double>(t1 - t0).count();
    logOperation("search", iterations, exec);
    return iterations;
}

/* ============================================================
 *   Eliminación (alto‑nivel)
 * ============================================================ */
void BTreeShip::remove(int key)
{
    if (!removeRec(key, rootNode)) {
        std::cout << "El valor no está en el árbol\n";
        return;
    }
    if (rootNode && rootNode->count == 0) {
        Node* tmp = rootNode;
        rootNode = rootNode->child[0];
        delete tmp;
    }
    elementSet.erase(key);
}

/* ============================================================
 *   Eliminación (recursiva)  ‑‑ solo lo imprescindible ‑‑
 *     (algoritmo clásico de B‑tree, ajustando
 *      underflow con merge/shift)
 * ============================================================ */
bool BTreeShip::removeRec(int key, Node* cur)
{
    if (!cur) return false;

    int pos;
    for (pos = 1; pos <= cur->count && key > cur->key[pos]; ++pos);

    /* encontrado en nodo interno/hoja                              */
    if (pos <= cur->count && key == cur->key[pos]) {
        if (cur->child[pos - 1]) {             // nodo interno
            int pred = getPred(cur->child[pos - 1]);
            cur->key[pos] = pred;
            removeRec(pred, cur->child[pos - 1]);
        } else {                               // hoja
            for (int i = pos; i < cur->count; ++i) {
                cur->key [i] = cur->key [i + 1];
                cur->child[i] = cur->child[i + 1];
            }
            --cur->count;
        }
    } else {
        /* seguir bajando                                             */
        if (!removeRec(key, cur->child[pos - 1])) return false;
    }

    /* underflow                                                     */
    if (cur->child[pos - 1] &&
        cur->child[pos - 1]->count < MIN_KEYS)
        fixUnderflow(cur, pos - 1);

    return true;
}

int BTreeShip::getPred(Node* cur)
{
    while (cur->child[cur->count])
        cur = cur->child[cur->count];
    return cur->key[cur->count];
}

void BTreeShip::fixUnderflow(Node* parent, int pos)
{
    if (pos > 0 && parent->child[pos - 1]->count > MIN_KEYS)
        shiftRight(parent, pos);
    else if (pos < parent->count &&
             parent->child[pos + 1]->count > MIN_KEYS)
        shiftLeft(parent, pos + 1);
    else
        merge(parent, (pos == parent->count) ? pos : pos + 1);
}

void BTreeShip::shiftLeft(Node* parent, int pos)
{
    Node* left  = parent->child[pos - 1];
    Node* right = parent->child[pos];

    /* lleva clave del padre a la izquierda                          */
    ++left->count;
    left->key [left->count]  = parent->key[pos];
    left->child[left->count] = right->child[0];

    /* sube primera clave del hermano                               */
    parent->key[pos] = right->key[1];

    for (int i = 1; i < right->count; ++i) {
        right->key [i] = right->key [i + 1];
        right->child[i] = right->child[i + 1];
    }
    right->child[right->count] = right->child[right->count + 1];
    --right->count;
}

void BTreeShip::shiftRight(Node* parent, int pos)
{
    Node* left  = parent->child[pos - 1];
    Node* right = parent->child[pos];

    for (int i = right->count; i >= 1; --i) {
        right->key  [i + 1] = right->key  [i];
        right->child[i + 1] = right->child[i];
    }
    right->child[1] = right->child[0];
    right->key  [1] = parent->key[pos];
    ++right->count;

    parent->key[pos] = left->key[left->count];
    right->child[0]  = left->child[left->count];
    --left->count;
}

void BTreeShip::merge(Node* parent, int pos)
{
    Node* left  = parent->child[pos - 1];
    Node* right = parent->child[pos];

    ++left->count;
    left->key [left->count]  = parent->key[pos];
    left->child[left->count] = right->child[0];

    for (int i = 1; i <= right->count; ++i) {
        ++left->count;
        left->key [left->count]  = right->key [i];
        left->child[left->count] = right->child[i];
    }
    delete right;

    for (int i = pos; i < parent->count; ++i) {
        parent->key  [i] = parent->key  [i + 1];
        parent->child[i] = parent->child[i + 1];
    }
    --parent->count;
}
