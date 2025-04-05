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
    WATER = 0,
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
    void drawGrid(RenderWindow& window);
    void drawShips(RenderWindow& window);
    void drawInfo(RenderWindow& window);
    void placeShip(int x, int y, int size, bool horizontal);
    void removeShip(int x, int y);
    void attackShip(int x, int y);
    void updateMatrix(int **matrix);
    void printText(RenderWindow& window, const std::string& text, int x, int y);
    void smokeExplosion(RenderWindow& window, int x, int y);
    

private:
    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture explosionTexture;
    Sprite explosionSprite;
    Texture shipTexture;
    Font font;
    Text infoText;
    Button buyButton;
    Button leftButton;
    Button rightButton;

    // grid
    int board[GRID_SIZE][GRID_SIZE]={0};
    int shipCount = 0;
    int shipSize = 1;
    bool attack = false;
    bool horizontal = false;

};

#endif // !GAMEMAPUI
