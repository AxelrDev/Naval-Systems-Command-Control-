#ifndef LINEARSEARCHSHIP_HPP
#define LINEARSEARCHSHIP_HPP

/**
 * @file LinearSearchShip.hpp
 * @brief Declares the LinearSearchShip class which implements a ship using linear search logic.
 */
#include "Ship.hpp"

class LinearSearchShip : public Ship {
private:
    /**
     * @struct Node
     * @brief Represents a node in the singly linked list storing elements.
     */
    struct Node {
        int nodeValue;  ///< Value stored in the node
        Node* nextNode; ///< Pointer to the next node in the list
        /**
         * @brief Constructs a node with the given value.
         * @param v Value to store.
         */
        Node(int v) : nodeValue(v), nextNode(nullptr) {}
    };
    Node* headNode; ///< Pointer to the first node in the list
    
    /**
     * @brief Generates the initial set of elements for the ship.
     */
    void generateElements();
public:
    /**
     * @brief Constructs a LinearSearchShip and initializes its list.
     */
    LinearSearchShip();
    /**
     * @brief Destructor. Frees all nodes in the list.
     */
    ~LinearSearchShip();

    /**
     * @brief Searches for a target value using linear search.
     * @param target Value to search for.
     * @return Number of iterations performed.
     */
    int  search(int target) override;
    /**
     * @brief Inserts a new element at the beginning of the list.
     * @param element Value to insert.
     */
    void insert(int element) override;
    /**
     * @brief Removes an element from the list.
     * @param element Value to remove.
     */
    void remove(int element) override;
};

#endif // LINEARSEARCHSHIP_H
