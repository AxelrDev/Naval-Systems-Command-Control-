#ifndef REDBLACKTREESHIP_HPP
#define REDBLACKTREESHIP_HPP

/**
 * @file RedBlackTreeShip.hpp
 * @brief Declares the RedBlackTreeShip class that implements a ship using a red-black tree structure.
 */

#include "Ship.hpp"

/**
 * @class RedBlackTreeShip
 * @brief A ship that uses a red-black tree to store and manage its elements.
 */
class RedBlackTreeShip : public Ship {
private:
    /**
     * @struct Node
     * @brief Represents a node in the red-black tree.
     */
    struct Node {
        int key;               ///< Key value stored in the node
        bool isRed;            ///< Color flag: true if red, false if black
        Node* parentNode;      ///< Pointer to parent node
        Node* leftChild;       ///< Pointer to left child
        Node* rightChild;      ///< Pointer to right child

        /**
         * @brief Constructs a new red node with the given key.
         * @param k Key to store.
         */
        Node(int k)
          : key(k), isRed(true),
            parentNode(nullptr), leftChild(nullptr), rightChild(nullptr)
        {}
    };

    Node* rootNode; ///< Root of the red-black tree

    // === Red-Black Tree Operations ===

    /**
     * @brief Performs a left rotation around the given node.
     * @param x Node to rotate.
     */
    void rotateLeft(Node* x);

    /**
     * @brief Performs a right rotation around the given node.
     * @param y Node to rotate.
     */
    void rotateRight(Node* y);

    /**
     * @brief Fixes red-black tree properties after insertion.
     * @param z Inserted node.
     * @param iterationCount Counter for iteration tracking.
     */
    void fixInsertion(Node* z, int &iterationCount);

    /**
     * @brief Inserts a new node with a key into the tree.
     * @param key Value to insert.
     * @param iterationCount Counter for iteration tracking.
     * @return Pointer to the inserted node.
     */
    Node* insertNode(int key, int &iterationCount);

    /**
     * @brief Searches for a node with the given key.
     * @param key Key to search.
     * @param iterationCount Counter for iteration tracking.
     * @return Pointer to the node if found, nullptr otherwise.
     */
    Node* searchNode(int key, int &iterationCount);

    /**
     * @brief Replaces one subtree with another.
     * @param u Subtree to be replaced.
     * @param v Subtree to replace with.
     */
    void transplant(Node* u, Node* v);

    /**
     * @brief Finds the minimum node in a subtree.
     * @param x Subtree root.
     * @return Node with minimum key.
     */
    Node* treeMinimum(Node* x);

    /**
     * @brief Fixes red-black tree properties after deletion.
     * @param x Node to fix.
     * @param iterationCount Counter for iteration tracking.
     */
    void fixDeletion(Node* x, int &iterationCount);

    /**
     * @brief Deletes a node from the tree.
     * @param z Node to delete.
     * @param iterationCount Counter for iteration tracking.
     */
    void deleteNode(Node* z, int &iterationCount);

    /**
     * @brief Deletes all nodes in the subtree rooted at node.
     * @param node Root of the subtree to delete.
     */
    void deleteSubtree(Node* node);

    /**
     * @brief Generates the initial elements to populate the tree.
     */
    void generateElements();

public:
    /**
     * @brief Constructs the RedBlackTreeShip and generates elements.
     */
    RedBlackTreeShip();

    /**
     * @brief Destructor that frees all memory.
     */
    ~RedBlackTreeShip() override;

    /**
     * @brief Searches for an element in the red-black tree.
     * @param target Value to search.
     * @return Number of iterations performed.
     */
    int search(int target) override;

    /**
     * @brief Inserts an element into the red-black tree.
     * @param element Value to insert.
     */
    void insert(int element) override;

    /**
     * @brief Removes an element from the red-black tree.
     * @param element Value to remove.
     */
    void remove(int element) override;
};

#endif // REDBLACKTREESHIP_HPP