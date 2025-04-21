#ifndef GAMEMAPUI
#define GAMEMAPUI


/**
 * @file GameMapUI.hpp
 * @brief Declares the GameMap class for rendering and managing the grid and gameplay events.
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ButtonUI.hpp>
#include "Player.hpp"
#include "Currency.hpp"
#include "GameShip.hpp"
#include "Constants.hpp"
using namespace sf;

/**
 * @enum cellState
 * @brief Represents the state of a cell in the game grid.
 */
enum cellState{
    WATER = -1,
    SHIP = 1,
    HIT = -1,
};

/**
 * @class GameMap
 * @brief Handles the game map logic, rendering, and player interaction.
 */
class GameMap {
public:
    /**
     * @brief Constructs a new GameMap instance and initializes the board.
     */
    GameMap();

    /**
     * @brief Runs the game loop, handling rendering and input.
     * @param window The SFML window for rendering.
     */
    void run(RenderWindow& window);
   
    /**
     * @brief Handles user input events.
     * @param window The SFML window.
     * @param event Event from SFML to handle.
     */
    void handleEvent(RenderWindow& window, Event& event);
    /**
     * @brief Draws the game board.
     * @param window SFML window to draw on.
     */
    void draw(RenderWindow& window);
    /**
     * @brief Displays a transition black screen between turns.
     * @param window SFML window.
     */
    void blackScreen(RenderWindow& window);
    
    /**
     * @brief Renders all game elements.
     * @param window SFML window.
     */
    void render(RenderWindow& window);
    
    /**
     * @brief Draws all ships on the board.
     * @param window SFML window.
     */
    void drawShips(RenderWindow& window);

    /**
     * @brief Draws game information text.
     * @param window SFML window.
     */
    void drawInfo(RenderWindow& window);

    /**
     * @brief Places a ship at a given position.
     * @param x Row coordinate.
     * @param y Column coordinate.
     * @param size Size of the ship.
     * @param horizontal True for horizontal orientation.
     */
    void placeShip(int x, int y, int size, bool horizontal);
    
    /**
     * @brief Removes a ship from the board.
     * @param x Row coordinate.
     * @param y Column coordinate.
     * @param player Player owning the ship.
     */
    void removeShip(int x, int y, Player* player);
   
    /**
     * @brief Attacks a specific cell on the board.
     * @param x Row coordinate.
     * @param y Column coordinate.
     */
    void attackShip(int x, int y);
    
    /**
     * @brief Updates internal board matrix.
     * @param matrix Pointer to new matrix.
     */
    void updateMatrix(int **matrix);

    /**
     * @brief Prints a text message on screen.
     * @param window SFML window.
     * @param text Text to print.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param color Text color.
     */
    void printText(RenderWindow& window, const std::string& text, int x, int y, const sf::Color color);

    /**
     * @brief Displays an explosion effect.
     * @param window SFML window.
     * @param x Row.
     * @param y Column.
     */
    void smokeExplosion(RenderWindow& window, int x, int y);

    /**
     * @brief Handles the button action when selecting a ship.
     * @param window SFML window.
     */
    void selectedButtonAction(RenderWindow& window);

    /**
     * @brief Checks if a ship is placed in a given cell.
     * @param x Row coordinate.
     * @param y Column coordinate.
     * @param board Board matrix.
     * @return True if ship is present, false otherwise.
     */
    bool isShipPlaced(int x, int y, int** board);

    /**
     * @brief Changes the active player's turn.
     * @return True if turn was changed.
     */
    bool changePlayerTurn();

    /**
     * @brief Resets game state for a new turn.
     */
    void reset();

    /**
     * @brief Stores ship placement information.
     * @param row Row coordinate.
     * @param col Column coordinate.
     * @param player Player placing the ship.
     */
    void addShipStorage(int row, int col, Player* player);

    /**
     * @brief Gets the current action state.
     * @return Integer representing the action.
     */
    int getAction();

    /**
     * @brief Allows player to purchase ships.
     * @param player Pointer to the player.
     */
    void buyShips(Player* player);

    /**
     * @brief Frees dynamically allocated memory.
     */
    void freeMemory();


private:
   /**
     * @brief Handles clicks on the grid area.
     * @param row Clicked row.
     * @param col Clicked column.
     * @param button Mouse button pressed.
     */
    void handleGridClick(int row, int col, sf::Mouse::Button button);
        /**
     * @brief Handles left mouse click actions such as placing or attacking ships.
     * @param row Clicked row.
     * @param col Clicked column.
     */
    void handleLeftClick(int row, int col);
        /**
     * @brief Handles right mouse click actions such as removing or selecting ships.
     * @param row Clicked row.
     * @param col Clicked column.
     */
    void handleRightClick(int row, int col);
        /**
     * @brief Handles clicks on ship purchase and selection buttons.
     * @param window SFML window where events are handled.
     */
    void handleBuyActions(sf::RenderWindow& window);
        /**
     * @brief Handles keyboard input for game mode switching.
     * @param key Pressed key.
     */
    void handleKeyInput(sf::Keyboard::Key key);
        /**
     * @brief Checks if the player is allowed to attack.
     * @return True if attack is possible.
     */
    bool canAttack();

    /**
     * @brief Checks whether a ship can be placed at the specified position.
     * 
     * @param player Pointer to the player attempting the placement.
     * @param row Row coordinate on the board.
     * @param col Column coordinate on the board.
     * @param turn Indicates the current player's turn.
     * @return true if the ship can be legally placed, false otherwise.
     */
    bool canPutShip(Player* player, int row, int col, bool turn);
        /**
     * @brief Manages selected ship display mode.
     * @param Window SFML render window.
     */
    void selectedMode(RenderWindow &Window);
        /**
     * @brief Draws the background of the game.
     * @param window SFML render window.
     */
    void drawBackground(RenderWindow& window);
        /**
     * @brief Draws UI buttons.
     * @param window SFML render window.
     */
    void drawButtons(RenderWindow& window);
        /**
     * @brief Draws game-related texts.
     * @param window SFML render window.
     */
    void drawTexts(RenderWindow& window);
        /**
     * @brief Highlights the currently selected ship.
     * @param window SFML render window.
     */
    void drawSelection(RenderWindow& window);
        /**
     * @brief Displays the victory screen with the winning player's text.
     * @param window SFML render window.
     * @param winnerText Text to display.
     */
    void showVictoryScreen(RenderWindow& window, const std::string& winnerText);


private:
    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture explosionTexture;
    Sprite explosionSprite;
    Texture shipTexture;
    Texture improvementPointsTexture;
    Sprite improvementPointsSprite;
    Font font;
    Text infoText;
    Button buyButton;
    Button leftBuyButton;
    Button rightBuyButton;
    Button buyPointsButton;
    std::vector<Texture> shipTextures;
    std::vector<Sprite> shipSprites;
    std::vector<string> cost;
    Player* player1;
    Player* player2;
    Currency currencyClass;
    

    // grid
    // Tablero de juego
    int board[GRID_SIZE][GRID_SIZE]={WATER};
    // Barcos colocados
    int shipCount = 0;
    int shipSize = 1;
    // Barco seleccionado
    int selectedShip = -1;
    // Barco a comprado
    int buyShip=0;
    int previousSelection = 0;
    // Atacar
    bool attack = false;
    bool horizontal = false;
    // Barcos seleccionado para atacar
    bool selected = false;
    // Turno del jugador
    bool playerTurn = true;
    // Coordenadas barco que ataca
    int xCord = -1;
    int yCord = -1;
    // Movimientos del jugador
    int movement = 5;
    // Dinero
    int currency = 0;

    bool changePlayer = false;

    int improvementPoints = 0;
};

#endif // !GAMEMAPUI