#ifndef BUTTONUI_HPP
#define BUTTONUI_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
public:
    Button(const Vector2f& position, const string& textureFile, const Vector2f& size = Vector2f(100, 50));
    
    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::RenderWindow& window) const;
    void setSize(const Vector2f& size);  // Método para ajustar el tamaño

private:
    RectangleShape buttonShape;
    Texture buttonTexture;
};

#endif
