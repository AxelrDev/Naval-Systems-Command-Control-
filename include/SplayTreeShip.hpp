#ifndef SPLAYTREESHIP_HPP
#define SPLAYTREESHIP_HPP

/**
 * @file SplayTreeShip.hpp
 * @brief Declares the SplayTreeShip class that implements a ship using a splay tree.
 */

#include "Ship.hpp"

/**
 * @class SplayTreeShip
 * @brief A ship that uses a splay tree to manage its elements for efficient access.
 */
class SplayTreeShip : public Ship {
private:
    /**
     * @struct Node
     * @brief Represents a node in the splay tree.
     */
    struct Node {
        int key;               ///< Key stored in the node
        Node* leftChild;       ///< Pointer to the left child
        Node* rightChild;      ///< Pointer to the right child
        Node* parentNode;      ///< Pointer to the parent node

        /**
         * @brief Constructs a node with the given key.
         * @param k Key value to assign.
         */
        Node(int k)
          : key(k),
            leftChild(nullptr), rightChild(nullptr), parentNode(nullptr)
        {}
    };

    Node* rootNode; ///< Root of the splay tree

    /**
     * @brief Performs a left rotation on the given node.
     * @param x Node to rotate.
     */
    void rotateLeft(Node* x);

    /**
     * @brief Performs a right rotation on the given node.
     * @param y Node to rotate.
     */
    void rotateRight(Node* y);

    /**
     * @brief Splays the tree at the given node, bringing it to the root.
     * @param node Node to splay.
     * @param iterationCount Counter to track operation cost.
     */
    void splayNode(Node* node, int &iterationCount);

    /**
     * @brief Inserts a node into the splay tree.
     * @param key Value to insert.
     * @param iterationCount Counter to track operation cost.
     * @return Pointer to the inserted node.
     */
    Node* insertNode(int key, int &iterationCount);

    /**
     * @brief Searches for a node with the given key.
     * @param key Value to search.
     * @param iterationCount Counter to track operation cost.
     * @return Pointer to the node if found, otherwise nullptr.
     */
    Node* searchNode(int key, int &iterationCount);

    /**
     * @brief Joins two splay trees into one.
     * @param leftTree Root of the left subtree.
     * @param rightTree Root of the right subtree.
     * @param iterationCount Counter to track operation cost.
     * @return Root of the resulting tree.
     */
    Node* joinTrees(Node* leftTree, Node* rightTree, int &iterationCount);

    /**
     * @brief Populates the tree with randomly generated elements.
     */
    void generateElements();

public:
    /**
     * @brief Constructs a SplayTreeShip and generates its elements.
     */
    SplayTreeShip();

    /**
     * @brief Searches for an element in the splay tree.
     * @param target Value to search.
     * @return Number of iterations performed.
     */
    int search(int target) override;

    /**
     * @brief Inserts an element into the splay tree.
     * @param element Value to insert.
     */
    void insert(int element) override;

    /**
     * @brief Removes an element from the splay tree.
     * @param element Value to remove.
     */
    void remove(int element) override;
};

#endif // SPLAYTREESHIP_H