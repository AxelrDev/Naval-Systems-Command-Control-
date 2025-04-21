#ifndef BUTTONUI_HPP
#define BUTTONUI_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/**
 * @class Button
 * @brief Represents a UI button with texture and mouse interaction using SFML.
 */
class Button {
public:
    /**
     * @brief Constructs a Button with a specified position, texture, and optional size.
     * @param position Position of the button on the window.
     * @param textureFile Path to the texture file to use as button background.
     * @param size Size of the button (default is 100x50).
     */
    Button(const Vector2f& position, const string& textureFile, const Vector2f& size = Vector2f(100, 50));

    /**
     * @brief Draws the button to the specified render window.
     * @param window The render window to draw the button on.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if the mouse is currently hovering over the button.
     * @param window The render window containing the mouse.
     * @return True if the mouse is over the button, false otherwise.
     */
    bool isMouseOver(const sf::RenderWindow& window) const;

    /**
     * @brief Sets a new size for the button.
     * @param size The new size as a Vector2f.
     */
    void setSize(const Vector2f& size);

private:
    RectangleShape buttonShape; ///< SFML shape representing the button
    Texture buttonTexture;      ///< Texture used for the button background
};

#endif