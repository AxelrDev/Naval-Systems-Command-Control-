#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ButtonUI.hpp>
// #include "Game.hpp"
#include "Player.hpp"
#include "Currency.hpp"
#include "GameShip.hpp"

using namespace sf;

#define GRID_SIZE 10
#define CELL_SIZE 50
#define NUM_SHIPS 4
#define INCREMENT 100
#define TURNS 10

enum cellState{
    WATER = -1,
    SHIP = 1,
    HIT = -1,
};

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    /**
     * @brief Ciclo principal del juego, mantiene la ventana abierta y responde a eventos.
     * @param window Ventana de SFML donde se ejecuta el juego.
     */
    void run(RenderWindow& window);
    /**
     * @brief Maneja todos los eventos de usuario, incluyendo mouse y teclado.
     * @param window Ventana activa.
     * @param event Evento capturado por SFML.
     */
    void handleEvent(RenderWindow& window, Event& event);
    /**
     * @brief Dibuja el fondo del tablero.
     * @param window Ventana donde se dibuja el fondo.
     */
    void draw(RenderWindow& window);
    /**
     * @brief Muestra una pantalla negra por unos segundos entre turnos.
     * @param window Ventana donde se muestra la pantalla negra.
     */
    void blackScreen(RenderWindow& window);
    /**
     * @brief Renderiza todos los elementos gráficos del juego en la ventana.
     * @param window Ventana donde se renderiza.
     */
    void render(RenderWindow& window);
    /**
     * @brief Dibuja los barcos colocados en el tablero.
     * @param window Ventana de SFML donde se dibujan los barcos.
     */
    void drawShips(RenderWindow& window);
    void drawInfo(RenderWindow& window);
    /**
     * @brief Coloca un barco en el tablero en posición horizontal o vertical.
     * @param row Fila inicial.
     * @param col Columna inicial.
     * @param size Tamaño del barco.
     * @param horizontal Verdadero si el barco es horizontal.
     */
    void placeShip(int x, int y, int size, bool horizontal);
    /**
     * @brief Elimina un barco de una celda específica del tablero.
     * @param row Fila donde está el barco.
     * @param col Columna donde está el barco.
     */
    void removeShip(int x, int y, Player* player);
   
    /**
     * @brief Ejecuta un ataque a una celda específica del tablero.
     * @param row Fila del tablero.
     * @param col Columna del tablero.
     */
    void attackShip(int x, int y);
    /**
     * @brief Actualiza la matriz interna del tablero con una matriz externa.
     * @param matrix Matriz de enteros que representa un nuevo estado del tablero.
     */
    void updateMatrix(int **matrix);
    /**
     * @brief Imprime un texto en la ventana en una posición específica.
     * @param window Referencia a la ventana SFML.
     * @param text Texto que se desea mostrar.
     * @param x Coordenada horizontal.
     * @param y Coordenada vertical.
     */
    void printText(RenderWindow& window, const std::string& text, int x, int y, const sf::Color color);
    void smokeExplosion(RenderWindow& window, int x, int y);
    /**
     * @brief Dibuja la acción del botón de selección de barco.
     * @param window Ventana donde se dibuja la acción del botón.
     */
    void selectedButtonAction(RenderWindow& window);
    /**
     * @brief Verifica si hay un barco colocado en una celda.
     * @param x Fila a verificar.
     * @param y Columna a verificar.
     * @return Verdadero si hay un barco, falso si es agua.
     */
    bool isShipPlaced(int x, int y, int** board);
    bool changePlayerTurn();
    /**
     * @brief Reinicia el estado de ataque y selección de barcos.
     */
    void reset();

    void addShipStorage(int row, int col, Player* player);

    int getAction();

    void buyShips(Player* player);

    void freeMemory();


private:
  /// @brief Maneja clics sobre el área de la grilla del mapa.
  /// @param row Fila clickeada.
  /// @param col Columna clickeada.
  /// @param button Botón del mouse presionado.
  void handleGridClick(int row, int col, sf::Mouse::Button button);

  /// @brief Maneja acciones del clic izquierdo (colocar barcos o atacar).
  /// @param row Fila del clic.
  /// @param col Columna del clic.
  void handleLeftClick(int row, int col);

  /// @brief Maneja acciones del clic derecho (remover o seleccionar barcos).
  /// @param row Fila del clic.
  /// @param col Columna del clic.
  void handleRightClick(int row, int col);

  /// @brief Maneja clics sobre botones de compra, selección, y navegación.
  /// @param window Referencia a la ventana donde se detectan los clics.
  void handleBuyActions(sf::RenderWindow& window);

  /// @brief Maneja eventos del teclado para cambiar de modo.
  /// @param key Tecla presionada.
  void handleKeyInput(sf::Keyboard::Key key);
    
  bool canAttack();
  bool canPutShip(Player* player, int row, int col,bool turn);

  void selectedMode(RenderWindow &Window);
  void drawBackground(RenderWindow& window);
  void drawButtons(RenderWindow& window);
  void drawTexts(RenderWindow& window);
  void drawSelection(RenderWindow& window);
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