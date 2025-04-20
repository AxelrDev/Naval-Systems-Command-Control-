#ifndef BTREESHIP_HPP
#define BTREESHIP_HPP

#include <iostream>
#include "Ship.hpp"
#include "Includes.hpp"

// Grado mínimo del B-Tree (t)
const int T = 3;

class BTreeNode {
public:
    BTreeNode(bool _leaf);

    // Recorre el subárbol en orden e imprime las claves
    void traverse();

    // Busca la clave k en el subárbol y devuelve el nodo donde se encuentra o nullptr
    BTreeNode* searching(int k,int &iterationCount);

    

    // Inserta una clave en un nodo no lleno
    void insertNonFull(int k,int &iterationCount);

    // Divide el hijo y de un nodo en y -> crea un nuevo nodo z
    void splitChild(int i, BTreeNode* y,int &iterationCount);

    // Elimina la clave k del subárbol
    void remove(int k,int &iterationCount);

    int keys[2*T - 1];       // Arreglo de claves
    BTreeNode* C[2*T];       // Arreglo de punteros a hijos
    int n;                   // Número actual de claves
    bool leaf;               // Verdadero si es nodo hoja

private:
    int findKey(int k, int &iterationCount);
    void removeFromLeaf(int idx,int &iterationCount);
    void removeFromNonLeaf(int idx,int &iterationCount);
    int getPred(int idx,int &iterationCount);
    int getSucc(int idx,int &iterationCount);
    void fill(int idx,int &iterationCount);
    void borrowFromPrev(int idx,int &iterationCount);
    void borrowFromNext(int idx,int &iterationCount);
    void merge(int idx,int &iterationCount);

};

class BTreeShip : public Ship {
public:
    BTreeShip();
    void traverse();
    BTreeNode* searching(int k,int &iterationCount);
    void insert(int k) override;
    void remove(int k) override;
    void generateElements();
    int  search(int target) override;

private:
    BTreeNode* root;
};

#endif // BTREE_HPP
