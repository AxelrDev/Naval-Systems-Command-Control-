#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"
#include "InfoUI.hpp"

using namespace sf;

class Menu {
public:
    Menu();
    void handleEvent(RenderWindow& window, Event& event, bool& isPlaying, bool& backToMenu);
    void draw(RenderWindow& window);

private:
    Button playButton;
    Button infoButton;
    Button exitButton;
    InfoPage info;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    bool inInfoPage;  // Bandera para saber si estamos en la página de info
};

#endif
