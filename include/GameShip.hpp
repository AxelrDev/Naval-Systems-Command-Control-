#ifndef GAMESHIP_HPP
#define GAMESHIP_HPP

#include "Ship.hpp"
#include "BinarySearchShip.hpp"
#include "BTreeShip.hpp"
#include "LinearSearchShip.hpp"
#include "RedBlackTreeShip.hpp"
#include "SetShip.hpp"
#include "SplayTreeShip.hpp"

class GameShip {
public:
    /**
     * @brief Constructs a GameShip with given position, health, damage and level.
     * @param row Row position on the board.
     * @param col Column position on the board.
     * @param vida Initial health.
     * @param damage Attack damage value.
     * @param level Ship level (for upgrades or classification).
     */
    GameShip(int row, int col, int vida, int damage, int level);

    /**
     * @brief Default constructor.
     */
    GameShip();
    
    /**
     * @brief Checks if the ship occupies a specific cell.
     * @param row Row coordinate to check.
     * @param col Column coordinate to check.
     * @return True if the ship occupies the given cell.
     */
    bool occupies(int row, int col) const;
    
    /**
     * @brief Applies damage to the ship.
     * @param damageAmount Amount of damage to apply.
     * @return True if the ship is destroyed after applying damage.
     */
    bool applyDamage(int damageAmount);
    
     /**
     * @brief Gets the ship's current health.
     * @return Remaining health (vida).
     */
    int getVida() const;

    /**
     * @brief Gets the ship's damage value.
     * @return Damage this ship can deal.
     */
    int getDamage() const;
    
     /**
     * @brief Gets the ship's current row position.
     * @return Row coordinate.
     */
    int getRow() const;

    /**
     * @brief Gets the ship's current column position.
     * @return Column coordinate.
     */
    int getCol() const;

    /**
     * @brief Sets the ship's position.
     * @param row New row position.
     * @param col New column position.
     */
    void setPosition(int row, int col);

    /**
     * @brief Gets the ship's level.
     * @return Ship level.
     */
    int getLevel();

    /**
     * @brief Checks whether this slot is empty.
     * @return True if no ship is present.
     */
    bool getEmpty();

    /**
     * @brief Marks this slot as empty or occupied.
     * @param empty True to mark empty, false otherwise.
     */
    void setEmpty(bool empty);

    /**
     * @brief Sets the specific type of ship based on its level or configuration.
     */
    void typeOfShip();

    /**
     * @brief Gets the ship's underlying implementation (type).
     * @return Pointer to the Ship object.
     */
    Ship *getTypeShip();

    private:
    int row;        ///< Row position of the ship on the board.
    int col;        ///< Column position of the ship on the board.
    int vida;       ///< Current health of the ship.
    int damage;     ///< Attack damage the ship can inflict.
    int level;      ///< Level of the ship.
    bool empty;     ///< Indicates if this ship slot is empty.
    Ship* typeShip; ///< Pointer to the ship's type (e.g., BTree, RedBlackTree, etc.)
};

#endif // GAMESHIP_HPP