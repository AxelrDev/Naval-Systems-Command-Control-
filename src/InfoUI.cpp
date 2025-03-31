#include "InfoUI.hpp"
#include <iostream>

InfoPage::InfoPage() 
: backButton(Vector2f(20, 10), "assets/img/menu_salir.png", Vector2f(96, 48))
, manualButton(Vector2f(128, 32), "assets/img/info_manual_click.png", Vector2f(288, 96))
, creditsButton(Vector2f(352, 32), "assets/img/info_creditos_click.png", Vector2f(384, 96))
{
    reset();
}

void InfoPage::reset() {
    if (!manualTexture.loadFromFile("assets/img/info_manual.png")) {
        std::cerr << "Error al cargar la textura del fondo de información." << std::endl;
    }
    if (!creditsTexture.loadFromFile("assets/img/info_creditos.png")) {
        std::cerr << "Error al cargar la textura del fondo de información." << std::endl;
    }
    backgroundSprite.setTexture(manualTexture);

    // Escalar el fondo a 455x256
    // float scaleX = 910.0f / backgroundTexture.getSize().x;
    // float scaleY = 512.0f / backgroundTexture.getSize().y;
    // backgroundSprite.setScale(scaleX, scaleY);
}

void InfoPage::handleEvent(RenderWindow& window, Event& event, bool& backToMenu) {
    if (event.type == Event::MouseButtonPressed) {
        if (backButton.isMouseOver(window)) {
            backToMenu = true;  // Volver al menú principal
        }
        else if (manualButton.isMouseOver(window)) {
            this->backgroundSprite.setTexture(manualTexture);
        }
        else if (creditsButton.isMouseOver(window)) {
            this->backgroundSprite.setTexture(creditsTexture);
        }
    }
}

void InfoPage::draw(RenderWindow& window) {
    window.draw(backgroundSprite);
    backButton.draw(window);
    manualButton.draw(window);
    creditsButton.draw(window);
}
