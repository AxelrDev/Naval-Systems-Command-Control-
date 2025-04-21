#ifndef GAME_HPP
#define GAME_HPP

#include "Currency.hpp"
#include "Player.hpp"

/**
 * @class Game
 * @brief Manages the core game logic including player turns and board configuration.
 */
class Game {
public:
    /**
     * @brief Constructs a Game object with the given board size, number of ships, and increment value.
     * @param rows Number of rows in the board.
     * @param cols Number of columns in the board.
     * @param numShips Number of ships per player.
     * @param increment Value used for increasing game difficulty or parameters.
     */
    Game(int rows, int cols, int numShips, int increment);

    /**
     * @brief Destructor. Cleans up allocated resources.
     */
    ~Game();

    /**
     * @brief Starts the player vs player game loop.
     */
    void play();

private:
    int rows;        ///< Number of rows in the board
    int cols;        ///< Number of columns in the board
    int numShips;    ///< Number of ships per player
    int increment;   ///< Increment value for scaling

    Player* player1; ///< Pointer to the first player
    Player* player2; ///< Pointer to the second player
    Currency* currency; ///< Pointer to currency manager

    /**
     * @brief Processes the turn of the current player against their opponent.
     * @param current The active player.
     * @param opponent The rival player.
     */
    void playerTurn(Player* current, Player* opponent);
};

#endif // GAME_HPP