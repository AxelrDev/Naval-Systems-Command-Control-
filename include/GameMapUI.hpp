#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void run(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event);
    void draw(RenderWindow& window);
    void blackScreen(RenderWindow& window);
private:

    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
};

#endif // !GAMEMAPUI
