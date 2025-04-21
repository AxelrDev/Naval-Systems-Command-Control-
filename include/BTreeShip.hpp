#ifndef BTREESHIP_HPP
#define BTREESHIP_HPP

#include <iostream>
#include "Ship.hpp"
#include "Includes.hpp"
#include "Constants.hpp"

const int T = 3;

class BTreeNode {
public:
    BTreeNode(bool _leaf);
    ~BTreeNode();

    
        /**
     * @brief Traverses and prints keys in this subtree.
     */
    void traverse();

    
        /**
     * @brief Searches for a key in this subtree.
     * @param k Key to search for.
     * @param iterationCount Counter for iterations.
     * @return Pointer to node containing the key or nullptr.
     */
    BTreeNode* searching(int k,int &iterationCount);

    

    
        /**
     * @brief Inserts a key into the subtree rooted at this node assuming it is not full.
     * @param k Key to insert.
     * @param iterationCount Counter for iterations.
     */
    void insertNonFull(int k,int &iterationCount);

    
        /**
     * @brief Splits the full child y of this node.
     * @param i Index of child to split.
     * @param y Pointer to the full child node.
     * @param iterationCount Counter for iterations.
     */
    void splitChild(int i, BTreeNode* y,int &iterationCount);

    
        /**
     * @brief Removes a key from the subtree rooted at this node.
     * @param k Key to remove.
     * @param iterationCount Counter for iterations.
     */
    void remove(int k,int &iterationCount);

    int keys[2*T - 1];       
    BTreeNode* C[2*T];       
    int n;                   
    bool leaf;               

private:
        /**
     * @brief Finds the index of the first key greater than or equal to k.
     * @param k Key to find.
     * @param iterationCount Counter for iterations.
     * @return Index of the key.
     */
    int findKey(int k, int &iterationCount);
        /**
     * @brief Removes the key present in the idx-th position in this node which is a leaf.
     * @param idx Index of key to remove.
     * @param iterationCount Counter for iterations.
     */
    void removeFromLeaf(int idx,int &iterationCount);
        /**
     * @brief Removes the key present in the idx-th position in this node which is not a leaf.
     * @param idx Index of key to remove.
     * @param iterationCount Counter for iterations.
     */
    void removeFromNonLeaf(int idx,int &iterationCount);
        /**
     * @brief Gets the predecessor of the key at index idx.
     * @param idx Index of key.
     * @param iterationCount Counter for iterations.
     * @return Predecessor key.
     */
    int getPred(int idx,int &iterationCount);
        /**
     * @brief Gets the successor of the key at index idx.
     * @param idx Index of key.
     * @param iterationCount Counter for iterations.
     * @return Successor key.
     */
    int getSucc(int idx,int &iterationCount);
        /**
     * @brief Fills the child node at idx-th position if it has less than the minimum number of keys.
     * @param idx Index of child.
     * @param iterationCount Counter for iterations.
     */
    void fill(int idx,int &iterationCount);
        /**
     * @brief Borrows a key from the previous sibling of the child at index idx.
     * @param idx Index of child.
     * @param iterationCount Counter for iterations.
     */
    void borrowFromPrev(int idx,int &iterationCount);
        /**
     * @brief Borrows a key from the next sibling of the child at index idx.
     * @param idx Index of child.
     * @param iterationCount Counter for iterations.
     */
    void borrowFromNext(int idx,int &iterationCount);
        /**
     * @brief Merges the idx-th child with its sibling.
     * @param idx Index of child to merge.
     * @param iterationCount Counter for iterations.
     */
    void merge(int idx,int &iterationCount);

};

/**
 * @class BTreeShip
 * @brief A ship implementation using a B-Tree structure to store elements.
 */
class BTreeShip : public Ship {
public:
        /**
     * @brief Constructor. Initializes the B-Tree with generated elements.
     */
    BTreeShip();
    ~    /**
     * @brief Constructor. Initializes the B-Tree with generated elements.
     */
    BTreeShip();
        /**
     * @brief Traverses and prints keys in this subtree.
     */
    void traverse();
        /**
     * @brief Searches for a key in this subtree.
     * @param k Key to search for.
     * @param iterationCount Counter for iterations.
     * @return Pointer to node containing the key or nullptr.
     */
    BTreeNode* searching(int k,int &iterationCount);
    void insert(int k) override;
    void remove(int k) override;
    void generateElements();
    int  search(int target) override;

private:
    BTreeNode* root;
};

#endif 