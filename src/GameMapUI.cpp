#include "MenuUI.hpp"
#include <SFML/Graphics.hpp>

RenderWindow window(VideoMode(910, 512), "Naval System", Style::Titlebar | Style::Close);

int main(){
    Menu menu;
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
            window.create(sf::VideoMode(910, 512), "Battle");
            window.setFramerateLimit(60);
        }
        else {
            menu.draw(window);
        }
        window.display();
    }



    return EXIT_SUCCESS;
}