#include "MenuUI.hpp"
#include <iostream>
Menu::Menu() :
    playButton(Vector2f(50, 400), "assets/img/jugar.png",Vector2f(284, 128)),
    infoButton(Vector2f(300, 400), "assets/img/info.png",Vector2f(284, 128)),
    exitButton(Vector2f(550, 400), "assets/img/salir.png",Vector2f(284, 128)),
    inInfoPage(false)
{
    if (!backgroundTexture.loadFromFile("assets/img/Battle_Ship_logo.png")) {
        std::cerr << "Error al cargar la textura del fondo del menú." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(Vector2f(0, 0));
}
void Menu::handleEvent(RenderWindow& window, Event& event, bool& isPlaying, bool& backToMenu) {
    if (inInfoPage) {
        info.handleEvent(window, event, backToMenu);
        if (backToMenu) {
            inInfoPage = false;  // Volver al menú principal
            backToMenu = false;  // Reiniciar la bandera
        }
    } else if (event.type == Event::MouseButtonPressed) {
        if (playButton.isMouseOver(window)) {
            isPlaying = true;
        } else if (infoButton.isMouseOver(window)) {
            inInfoPage = true;
            info.reset();  // Recargar la pantalla de info al ingresar
        } else if (exitButton.isMouseOver(window)) {
            window.close();
        }
    }
}
void Menu::draw(RenderWindow& window) {
    if (inInfoPage) {
        info.draw(window);
    } else {
        window.draw(backgroundSprite);
        playButton.draw(window);
        infoButton.draw(window);
        exitButton.draw(window);
    }
}