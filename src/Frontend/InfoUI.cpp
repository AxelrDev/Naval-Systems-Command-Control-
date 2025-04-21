#include "InfoUI.hpp"
#include <iostream>

InfoPage::InfoPage()
: backButton(Vector2f(20, 10), "assets/img/salir.png",
    Vector2f(96, 48))
, manualButton(Vector2f(100, 10), "assets/img/manual.png", 
    Vector2f(96, 48))
, creditsButton(Vector2f(180, 10), "assets/img/credits.png",
    Vector2f(96, 48))
{ 
  reset();
}

void InfoPage::reset() {
  if (!manualTexture.loadFromFile("assets/img/UserManual.png")) {
    std::cerr << "Error al cargar la textura del fondo de información." <<
        std::endl;
  }
  if (!creditsTexture.loadFromFile("assets/img/SDOC.png")) {
    std::cerr << "Error al cargar la textura del fondo de información." <<
        std::endl;
  }
  backgroundSprite.setTexture(manualTexture);
}

void InfoPage::handleEvent(RenderWindow& window, Event& event, bool& backToMenu) {
  if (event.type == Event::MouseButtonPressed) {
      if (backButton.isMouseOver(window)) {
          backToMenu = true; 
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

