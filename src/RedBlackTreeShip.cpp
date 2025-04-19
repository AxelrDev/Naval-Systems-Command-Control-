#include "RedBlackTreeShip.h"
#include "Constants.h"
#include <chrono>
#include <cstdlib>

RedBlackTreeShip::RedBlackTreeShip()
  : Ship("RedBlackTree", PRICE_REDBLACK_TREE),
    rootNode(nullptr)
{
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        insert(rand() % 1000);
    }
}


RedBlackTreeShip::~RedBlackTreeShip() {
    deleteSubtree(rootNode);
}

void RedBlackTreeShip::deleteSubtree(Node* node) {
    if (!node) return;
    deleteSubtree(node->leftChild);
    deleteSubtree(node->rightChild);
    delete node;
}

int RedBlackTreeShip::search(int target) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    Node* current = rootNode;
    while (current) {
        ++iterationCount;
        if (target == current->key) break;
        current = (target < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("search", iterationCount, execTime);
    return iterationCount;
}

void RedBlackTreeShip::insert(int element) {
    if (elementSet.count(element)) return;
    Node* newNode = insertNode(element);
    if (newNode) fixInsertion(newNode);
    if (rootNode) rootNode->isRed = false;
    elementSet.insert(element);
}

void RedBlackTreeShip::remove(int element) {
    Node* z = searchNode(element);
    if (!z) return;
    deleteNode(z);
    elementSet.erase(element);
}

RedBlackTreeShip::Node* RedBlackTreeShip::insertNode(int key) {
    Node* newNode = new Node(key);
    Node* parent   = nullptr;
    Node* current  = rootNode;

    while (current) {
        parent = current;
        if (newNode->key < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    newNode->parentNode = parent;

    if (!parent){
        rootNode = newNode;
    }
    else if (newNode->key < parent->key){
        parent->leftChild = newNode;
    }
    else{
        parent->rightChild = newNode;
    }
    return newNode;
}

void RedBlackTreeShip::fixInsertion(Node* z) {
    while (z != rootNode && z->parentNode->isRed) {
        Node* parent      = z->parentNode;
        Node* grandparent = parent->parentNode;

        if (parent == grandparent->leftChild) {
            Node* uncle = grandparent->rightChild;
            if (uncle && uncle->isRed) {
                parent->isRed = uncle->isRed = false;
                grandparent->isRed = true;
                z = grandparent;
            } else {
                if (z == parent->rightChild) {
                    z = parent;
                    rotateLeft(z);
                    parent = z->parentNode;
                }
                parent->isRed      = false;
                grandparent->isRed = true;
                rotateRight(grandparent);
            }
        } else {
            Node* uncle = grandparent->leftChild;
            if (uncle && uncle->isRed) {
                parent->isRed = uncle->isRed = false;
                grandparent->isRed = true;
                z = grandparent;
            } else {
                if (z == parent->leftChild) {
                    z = parent;
                    rotateRight(z);
                    parent = z->parentNode;
                }
                parent->isRed      = false;
                grandparent->isRed = true;
                rotateLeft(grandparent);
            }
        }
    }
    rootNode->isRed = false;
}

void RedBlackTreeShip::rotateLeft(Node* node) {
    // Pivotar hacia la izquierda en 'node'
    Node* pivot = node->rightChild;
    node->rightChild = pivot->leftChild;

    if (pivot->leftChild)
        pivot->leftChild->parentNode = node;

    pivot->parentNode = node->parentNode;
    if (!node->parentNode)
        rootNode = pivot;
    else if (node == node->parentNode->leftChild)
        node->parentNode->leftChild = pivot;
    else
        node->parentNode->rightChild = pivot;

    pivot->leftChild = node;
    node->parentNode = pivot;
}

void RedBlackTreeShip::rotateRight(Node* node) {
    // Pivotar hacia la derecha en 'node'
    Node* pivot = node->leftChild;
    node->leftChild = pivot->rightChild;

    if (pivot->rightChild)
        pivot->rightChild->parentNode = node;

    pivot->parentNode = node->parentNode;
    if (!node->parentNode)
        rootNode = pivot;
    else if (node == node->parentNode->rightChild)
        node->parentNode->rightChild = pivot;
    else
        node->parentNode->leftChild = pivot;

    pivot->rightChild = node;
    node->parentNode   = pivot;
}


RedBlackTreeShip::Node* RedBlackTreeShip::searchNode(int key) {
    Node* current = rootNode;
    while (current && current->key != key) {
        current = (key < current->key)
                ? current->leftChild
                : current->rightChild;
    }
    return current;
}

void RedBlackTreeShip::transplant(Node* u, Node* v) {
    if (!u->parentNode)        rootNode = v;
    else if (u == u->parentNode->leftChild)  u->parentNode->leftChild  = v;
    else                                     u->parentNode->rightChild = v;
    if (v) v->parentNode = u->parentNode;
}

RedBlackTreeShip::Node* RedBlackTreeShip::treeMinimum(Node* x) {
    while (x->leftChild) x = x->leftChild;
    return x;
}

void RedBlackTreeShip::deleteNode(Node* targetNode) {
    Node* nodeToRemove     = targetNode;
    bool originalWasRed     = nodeToRemove->isRed;
    Node* replacementNode  = nullptr;

    // Si no tiene hijo izquierdo
    if (!targetNode->leftChild) {
        replacementNode = targetNode->rightChild;
        transplant(targetNode, targetNode->rightChild);

    // Si no tiene hijo derecho
    } else if (!targetNode->rightChild) {
        replacementNode = targetNode->leftChild;
        transplant(targetNode, targetNode->leftChild);

    // Caso: dos hijos
    } else {
        // Encontrar el sucesor (mínimo en subárbol derecho)
        Node* successor    = treeMinimum(targetNode->rightChild);
        originalWasRed     = successor->isRed;
        replacementNode    = successor->rightChild;

        if (successor->parentNode == targetNode) {
            if (replacementNode)
                replacementNode->parentNode = successor;
        } else {
            transplant(successor, successor->rightChild);
            successor->rightChild = targetNode->rightChild;
            successor->rightChild->parentNode = successor;
        }

        transplant(targetNode, successor);
        successor->leftChild = targetNode->leftChild;
        successor->leftChild->parentNode = successor;
        successor->isRed = targetNode->isRed;
    }

    delete targetNode;

    // Si removimos un nodo negro, reparar posibles desequilibrios
    if (!originalWasRed) {
        fixDeletion(replacementNode);
    }
}

void RedBlackTreeShip::fixDeletion(Node* node) {
    // Reparar hasta que el nodo llegue a la raíz o se vuelva rojo
    while (node != rootNode && (!node || !node->isRed)) {
        Node* parent  = node ? node->parentNode : nullptr;

        // Si es hijo izquierdo
        if (parent && node == parent->leftChild) {
            Node* sibling = parent->rightChild;

            // 1) Hermano rojo → recolorear y rotar a la izquierda
            if (sibling && sibling->isRed) {
                sibling->isRed    = false;
                parent->isRed     = true;
                rotateLeft(parent);
                sibling = parent->rightChild;
            }

            // 2) Ambos hijos del hermano son negros → pintar hermano de rojo
            if (sibling
                && (!sibling->leftChild  || !sibling->leftChild->isRed)
                && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                sibling->isRed = true;
                node = parent;

            // 3) Al menos un hijo del hermano es rojo
            } else {
                // 3a) El hijo derecho del hermano es negro → rotar a la derecha en el hermano
                if (sibling && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                    if (sibling->leftChild)
                        sibling->leftChild->isRed = false;
                    sibling->isRed = true;
                    rotateRight(sibling);
                    sibling = parent->rightChild;
                }
                // 3b) Recolor y rotar a la izquierda en el padre
                if (sibling)
                    sibling->isRed = parent->isRed;
                parent->isRed = false;
                if (sibling && sibling->rightChild)
                    sibling->rightChild->isRed = false;
                rotateLeft(parent);
                node = rootNode;
            }

        // Caso espejo: si es hijo derecho
        } else {
            if (!parent) break;
            Node* sibling = parent->leftChild;

            if (sibling && sibling->isRed) {
                sibling->isRed    = false;
                parent->isRed     = true;
                rotateRight(parent);
                sibling = parent->leftChild;
            }

            if (sibling
                && (!sibling->leftChild  || !sibling->leftChild->isRed)
                && (!sibling->rightChild || !sibling->rightChild->isRed)) {
                sibling->isRed = true;
                node = parent;
            } else {
                if (sibling && (!sibling->leftChild || !sibling->leftChild->isRed)) {
                    if (sibling->rightChild)
                        sibling->rightChild->isRed = false;
                    sibling->isRed = true;
                    rotateLeft(sibling);
                    sibling = parent->leftChild;
                }
                if (sibling)
                    sibling->isRed = parent->isRed;
                parent->isRed = false;
                if (sibling && sibling->leftChild)
                    sibling->leftChild->isRed = false;
                rotateRight(parent);
                node = rootNode;
            }
        }
    }

    if (node)
        node->isRed = false;
}

