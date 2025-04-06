#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ButtonUI.hpp>

using namespace sf;

#define GRID_SIZE 10
#define CELL_SIZE 50

enum cellState{
    WATER = -1,
    SHIP = 1,
    HIT = 2,
};




class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void run(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event);
    void draw(RenderWindow& window);
    void blackScreen(RenderWindow& window);
    void render(RenderWindow& window);
    void drawShips(RenderWindow& window);
    void drawInfo(RenderWindow& window);
    void placeShip(int x, int y, int size, bool horizontal);
    void removeShip(int x, int y);
    void attackShip(int x, int y);
    void updateMatrix(int **matrix);
    void printText(RenderWindow& window, const std::string& text, int x, int y);
    void smokeExplosion(RenderWindow& window, int x, int y);
    void selectedButtonAction(RenderWindow& window);
    

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
    Button selectedButton;
    Button leftShipButton;
    Button rightShipButton;
    Button buyPointsButton;
    std::vector<Texture> shipTextures;
    std::vector<Sprite> shipSprites;
    std::vector<string> cost;

    // grid
    int board[GRID_SIZE][GRID_SIZE]={WATER};
    int shipCount = 0;
    int shipSize = 1;
    int selectedShip = 0;
    int Ship=0;
    int previousSelection = 0;
    bool attack = false;
    bool horizontal = false;
    string currency = "0";

};

#endif // !GAMEMAPUI
