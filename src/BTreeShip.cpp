#include "BTreeShip.h"
#include <iostream>
#include <algorithm>


using namespace std;

BTreeShip::BTreeShip(std::string name, int price)
    : Ship(name, price), root(nullptr) {}

BTreeShip::~BTreeShip() {
    // (Opcional) liberar memoria de los nodos si se desea
}

// Crear nuevo nodo
BTreeShip::BTreeNode* BTreeShip::createNode(int val, BTreeNode* child) {
    BTreeNode* newNode = new BTreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

// Agregar valor a nodo
void BTreeShip::addValToNode(int val, int pos, BTreeNode* node, BTreeNode* child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

// Dividir nodo
void BTreeShip::splitNode(int val, int* pval, int pos, BTreeNode* node, BTreeNode* child, BTreeNode** newNode) {
    int median = (pos > MIN) ? MIN + 1 : MIN;
    *newNode = new BTreeNode;

    for (int j = median + 1; j <= MAX; ++j) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
    }

    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN)
        addValToNode(val, pos, node, child);
    else
        addValToNode(val, pos - median, *newNode, child);

    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

// Insertar valor en nodo
int BTreeShip::setValueInNode(int val, int* pval, BTreeNode* node, BTreeNode** child) {
    int pos;

    if (!node) {
        *pval = val;
        *child = nullptr;
        return 1;
    }

    if (val < node->val[1]) {
        pos = 0;
    } else {
        for (pos = node->count; (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            cout << "Valor duplicado no permitido\n";
            return 0;
        }
    }

    if (setValueInNode(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }

    return 0;
}

// Insertar valor público
void BTreeShip::insert(int val) {
    int i;
    BTreeNode* child;
    int flag = setValueInNode(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);

    elementSet.insert(val);
    elements.push_back(val);
}

// Copiar sucesor
void BTreeShip::copySuccessor(BTreeNode* myNode, int pos) {
    BTreeNode* dummy = myNode->link[pos];
    while (dummy->link[0] != nullptr)
        dummy = dummy->link[0];
    myNode->val[pos] = dummy->val[1];
}

// Remover valor del nodo
void BTreeShip::removeVal(BTreeNode* myNode, int pos) {
    for (int i = pos + 1; i <= myNode->count; i++) {
        myNode->val[i - 1] = myNode->val[i];
        myNode->link[i - 1] = myNode->link[i];
    }
    myNode->count--;
}

// Rotaciones y ajustes
void BTreeShip::doRightShift(BTreeNode* myNode, int pos) {
    BTreeNode* x = myNode->link[pos];
    for (int j = x->count; j > 0; j--) {
        x->val[j + 1] = x->val[j];
        x->link[j + 1] = x->link[j];
    }
    x->val[1] = myNode->val[pos];
    x->link[1] = x->link[0];
    x->count++;

    x = myNode->link[pos - 1];
    myNode->val[pos] = x->val[x->count];
    myNode->link[pos] = x->link[x->count];
    x->count--;
}

void BTreeShip::doLeftShift(BTreeNode* myNode, int pos) {
    BTreeNode* x = myNode->link[pos - 1];
    x->count++;
    x->val[x->count] = myNode->val[pos];
    x->link[x->count] = myNode->link[pos]->link[0];

    x = myNode->link[pos];
    myNode->val[pos] = x->val[1];
    x->link[0] = x->link[1];
    x->count--;

    for (int j = 1; j <= x->count; j++) {
        x->val[j] = x->val[j + 1];
        x->link[j] = x->link[j + 1];
    }
}

void BTreeShip::mergeNodes(BTreeNode* myNode, int pos) {
    BTreeNode* x1 = myNode->link[pos];
    BTreeNode* x2 = myNode->link[pos - 1];
    x2->count++;
    x2->val[x2->count] = myNode->val[pos];
    x2->link[x2->count] = x1->link[0];

    for (int j = 1; j <= x1->count; j++) {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->link[x2->count] = x1->link[j];
    }

    for (int j = pos; j < myNode->count; j++) {
        myNode->val[j] = myNode->val[j + 1];
        myNode->link[j] = myNode->link[j + 1];
    }

    myNode->count--;
    delete x1;
}

void BTreeShip::adjustNode(BTreeNode* myNode, int pos) {
    if (!pos) {
        if (myNode->link[1]->count > MIN)
            doLeftShift(myNode, 1);
        else
            mergeNodes(myNode, 1);
    } else {
        if (myNode->count != pos) {
            if (myNode->link[pos - 1]->count > MIN)
                doRightShift(myNode, pos);
            else if (myNode->link[pos + 1]->count > MIN)
                doLeftShift(myNode, pos + 1);
            else
                mergeNodes(myNode, pos);
        } else {
            if (myNode->link[pos - 1]->count > MIN)
                doRightShift(myNode, pos);
            else
                mergeNodes(myNode, pos);
        }
    }
}

// Eliminar valor recursivamente
int BTreeShip::delValFromNode(int val, BTreeNode* myNode) {
    int pos;
    bool flag = false;

    if (myNode) {
        if (val < myNode->val[1]) {
            pos = 0;
        } else {
            for (pos = myNode->count; (val < myNode->val[pos] && pos > 1); pos--);
            if (val == myNode->val[pos]) flag = true;
        }

        if (flag) {
            if (myNode->link[pos - 1]) {
                copySuccessor(myNode, pos);
                flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
            } else {
                removeVal(myNode, pos);
            }
        } else {
            flag = delValFromNode(val, myNode->link[pos]);
        }

        if (myNode->link[pos] && myNode->link[pos]->count < MIN)
            adjustNode(myNode, pos);
    }

    return flag;
}

// Eliminar valor público
void BTreeShip::remove(int val) {
    if (!delValFromNode(val, root)) {
        cout << "El valor no está en el árbol\n";
        return;
    }

    if (root->count == 0) {
        BTreeNode* tmp = root;
        root = root->link[0];
        delete tmp;
    }

    elementSet.erase(val);
    elements.erase(std::remove(elements.begin(), elements.end(), val), elements.end());
}

// Buscar valor
void BTreeShip::searchingRecursive(int val, int* pos, BTreeNode* myNode) {
    if (!myNode) return;

    if (val < myNode->val[1]) {
        *pos = 0;
    } else {
        for (*pos = myNode->count; (val < myNode->val[*pos] && *pos > 1); (*pos)--);
        if (val == myNode->val[*pos]) {
            return;
        }
    }

    searchingRecursive(val, pos, myNode->link[*pos]);
}

int BTreeShip::search(int val) {
    int pos = 0;
    searchingRecursive(val, &pos, root);

    // Verificación con set por simplicidad de implementación
    return elementSet.count(val) ? 1 : -1;
}
