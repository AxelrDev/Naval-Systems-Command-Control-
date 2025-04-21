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
constexpr int PRICE_BINARY_SEARCH   = 110;

/**
 * @brief Price of the Set-based Ship.
 */
constexpr int PRICE_SET             = 120;

/**
 * @brief Price of the Red-Black Tree Ship.
 */
constexpr int PRICE_REDBLACK_TREE   = 150;

/**
 * @brief Price of the Splay Tree Ship.
 */
constexpr int PRICE_SPLAY_TREE      = 160;

/**
 * @brief Constant used to calculate damage: DAMAGE = DAMAGE_CONSTANT / iterations.
 */
constexpr int DAMAGE_CONSTANT       = 1000;

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
#define NUM_SHIPS 1

/**
 * @brief Value increment step for some parameters.
 */
#define INCREMENT 100

/**
 * @brief Total number of turns in the game.
 */
#define TURNS 1000

#endif // CONSTANTS_HPP