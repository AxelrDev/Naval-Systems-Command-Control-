#include "ButtonUI.hpp"
#include <iostream>

Button::Button(const Vector2f& position, const string& textureFile, 
    const Vector2f& size) {
  if (!buttonTexture.loadFromFile(textureFile)) {
    std::cerr << "Error al cargar la textura del botón." << std::endl;
  }

  buttonShape.setSize(size);
  buttonShape.setTexture(&buttonTexture);
  buttonShape.setPosition(position);
}

void Button::draw(sf::RenderWindow& window) {
  window.draw(buttonShape);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
  Vector2i mousePos = Mouse::getPosition(window);
  FloatRect buttonBounds = buttonShape.getGlobalBounds();
  return buttonBounds.contains(static_cast<Vector2f>(mousePos));
}

void Button::setSize(const Vector2f& size) {
  buttonShape.setSize(size);
}
