#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

#define GRID_SIZE 10
#define CELL_SIZE 50

enum cellState{
    WATER = 0,
    SHIP = 1,
    HIT = 2,
};

struct Ship{
    int size;
    int row, col;
    bool horizontal;
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
    void drawGrid(RenderWindow& window);
    void drawShips(RenderWindow& window);
    void drawInfo(RenderWindow& window);
    void placeShip(int x, int y, int size, bool horizontal);
    void removeShip(int x, int y);
    void attackShip(int x, int y);
    void updateMatrix(int **matrix);
    void printText(RenderWindow& window, const std::string& text, int x, int y);
    

private:
    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture shipTexture;
    Font font;
    Text infoText;

    // grid
    int board[GRID_SIZE][GRID_SIZE]={0};

    std::vector<Ship> ships;
    int shipCount = 0;
    int shipSize = 1;
    bool attack = false;
    bool horizontal = false;

    std::map<int, int>shipLimits = {
        {2, 1},
        {3, 2},
        {4, 1},
        {5, 1}
    };
    std::map<int, int>shipCountMap = {
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0}
    };
};

#endif // !GAMEMAPUI
