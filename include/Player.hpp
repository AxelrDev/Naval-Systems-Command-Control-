#ifndef PLAYER_HPP
#define PLAYER_HPP

/**
 * @file Player.hpp
 * @brief Declares the Player class used for managing a player's ships, board, and actions.
 */
#include <vector>
#include "GameShip.hpp"

/**
 * @class Player
 * @brief Represents a player in the game, including their ships, board, money, and actions.
 */
class Player {
public:
    /**
     * @brief Constructs a player with a board of given dimensions.
     * @param rows Number of rows.
     * @param cols Number of columns.
     */
    Player(int rows, int cols);

    /**
     * @brief Destructor. Cleans up dynamically allocated resources.
     */
    ~Player();

    /**
     * @brief Places ships randomly on the board.
     * @param numShips Number of ships to place.
     * @param levelShip Level of ships.
     */
    void placeShips(int numShips, int levelShip);
    
    /**
     * @brief Processes a shot received on the player's board.
     * @param row Row of the shot.
     * @param col Column of the shot.
     * @param damage Damage to apply.
     * @return True if a ship was hit.
     */
    bool receiveShot(int row, int col, int damage);
    
    /**
     * @brief Records the result of a shot fired at the opponent.
     * @param row Row of the shot.
     * @param col Column of the shot.
     * @param hit True if the shot hit a ship.
     */
    void recordShot(int row, int col, bool hit);

    /**
     * @brief Gets the damage value of a ship at a specific position.
     * @param row Row of the ship.
     * @param col Column of the ship.
     * @return Damage value.
     */
    int getShipDamage(int row, int col);

    /**
     * @brief Displays the player's own board.
     */
    void displayOwnBoard();

    /**
     * @brief Displays the tracking board (opponent shot results).
     */
    void displayTrackingBoard();
    
    /**
     * @brief Checks if all player's ships are sunk.
     * @return True if all ships are destroyed.
     */
    bool allShipsSunk();
    
    /**
     * @brief Gets the number of available actions for the player.
     * @return Number of actions remaining this turn.
     */
    int getaction();

    /**
     * @brief Decreases the number of available actions by one.
     */
    void setLessAction();

    /**
     * @brief Sets a specific number of actions available for the turn.
     * @param newAction The number of actions to assign.
     */
    void setaction(int newAction);
    
    /**
     * @brief Moves a ship to a new position on the board.
     * @return True if the move was successful.
     */
    bool moveShip();

    /**
     * @brief Gets the player's current money.
     * @return Money available.
     */
    int getMoney();

    /**
     * @brief Subtracts the cost of a ship from the player's money.
     * @param amount Cost to subtract.
     * @return True if the player has enough money.
     */
    bool lessMoney(int amount);

    /**
     * @brief Adds money to the player's total.
     * @param amount Amount to add.
     */
    void plusMoney(int amount);

    /**
     * @brief Upgrades a ship at a specific location.
     * @param row Row of the ship.
     * @param col Column of the ship.
     */
    void upGradeShip(int row, int col);

    /**
     * @brief Gets a pointer to the player's own game board.
     * @return Pointer to a 2D array representing the player's board.
     */
    int** getboard();

    /**
     * @brief Gets a pointer to the matrix used to track the player's own changes or attacks.
     * @return Pointer to a 2D array used for tracking changes.
     */
    int** getChangeMatrix();

    /**
     * @brief Gets a pointer to the board tracking shots made at the opponent.
     * @return Pointer to a 2D array representing the tracking board.
     */
    int** getTrackingBoard();

    /**
     * @brief Increments the number of improvement points.
     */
    void plusImprovementPoints();
    /**
     * @brief Sets the ship storage as empty.
     */
    void setShipStorageEmpty();
    /**
     * @brief Applies an attack pattern or resets the attack matrix.
     */
    void attackMatrix();
    /**
     * @brief Initializes or resets the player's board.
     */
    void setPlayerBoard();
    /**
     * @brief Gets the available improvement points.
     * @return Number of points.
     */
    int getImprovementPoints();

    /**
     * @brief Checks if the ship storage is empty.
     * @return True if empty.
     */
    bool isShipempty();

    /**
     * @brief Gets the ship in storage.
     * @return Stored GameShip.
     */
    GameShip getShipStorage();

    /**
     * @brief Sets the ship in storage.
     * @param ship GameShip to store.
     */
    void setShipStorage(GameShip ship);

    /**
     * @brief Gets the player's vector of ships.
     * @return Reference to ship vector.
     */
    std::vector<GameShip>& getShips();

private:
    int rows;                  ///< Number of board rows
    int cols;                  ///< Number of board columns
    int money;                 ///< Player's money
    int** ownBoard;            ///< Player's ship board
    int** changeMatrix;        ///< Matrix for tracking player's shots
    std::vector<GameShip> ships; ///< Vector of player's ships
    GameShip shipStorage;      ///< Ship storage (for selection, move, etc.)
    int improvementPoints;     ///< Points for upgrading ships
    int actions;               ///< Number of actions available per turn

    /**
     * @brief Initializes both the ownBoard and tracking board with empty values.
     */
    void initializeBoards();
};

#endif // PLAYER_HPP
