#include "MenuUI.hpp"
#include <iostream>
#include "GameMapUI.hpp"
#include <SFML/Graphics.hpp>


using namespace sf;


int main(){
    RenderWindow window(VideoMode(910, 512), "Naval System", Style::Titlebar | Style::Close);
    Menu menu;
    GameMap gameMap = GameMap();
    bool isPlaying = false;
    bool backToMenu = false;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            menu.handleEvent(window, event, isPlaying, backToMenu);
        }

        window.clear();
        if (isPlaying) {
            // Restablecer ventana escalable
            window.create(sf::VideoMode(800, 800), "Battle");
            window.setFramerateLimit(60);
            gameMap.run(window);

            if (event.type == Event::Closed) {
                isPlaying=false;
                window.close();
            }
        }
        else {
            menu.draw(window);
        }
        window.display();
        // Esperar 1 segundo antes de mostrar la pantalla negra
        
    }
}