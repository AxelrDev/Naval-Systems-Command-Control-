#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/**
 * @file Constants.hpp
 * @brief Contains global constants used throughout the game.
 */

/**
 * @brief Number of elements initialized randomly in each ship.
 */
constexpr int NUM_OF_ELEMENTS    = 1000;

/**
 * @brief Maximum number of elements for the random.
 */
constexpr int MAX_NUM_ELEMENTS   = NUM_OF_ELEMENTS * 3;

/**
 * @brief Amount of currency received by a player per turn.
 */
constexpr int CURRENCY_PER_TURN  = 50;

/**
 * @brief Price of the Linear Search Ship.
 */
constexpr int PRICE_LINEAR_SEARCH   = 100;

/**
 * @brief Price of the Binary Search Ship.
 */
constexpr int PRICE_BINARY_SEARCH   = 200;

/**
 * @brief Price of the Set-based Ship.
 */
constexpr int PRICE_SET             = 600;

/**
 * @brief Price of the Red-Black Tree Ship.
 */
constexpr int PRICE_REDBLACK_TREE   = 500;

/**
 * @brief Price of the Splay Tree Ship.
 */
constexpr int PRICE_SPLAY_TREE      = 400;

/**
 * @brief Price of the BTREE Ship.
 */
constexpr int PRICE_BTHREE          = 300;

/**
 * @brief Constant used to calculate damage: DAMAGE = DAMAGE_CONSTANT / iterations.
 */
constexpr int DAMAGE_CONSTANT       = 700;

/**
 * @brief Initial life value for each ship.
 */
constexpr int LIFE                  = 1000;

/**
 * @brief Grid dimensions (GRID_SIZE x GRID_SIZE).
 */
#define GRID_SIZE 10

/**
 * @brief Size (in pixels) of each cell in the grid.
 */
#define CELL_SIZE 50

/**
 * @brief Number of ships used in the game.
 */
#define NUM_SHIPS 3

/**
 * @brief Value increment step for some parameters.
 */
#define INCREMENT 50

/**
 * @brief Total number of turns in the game.
 */
#define TURNS 3
/**
 * @brief Initial amount of money for the player.
 */
#define MONEY 100

#endif // CONSTANTS_HPP