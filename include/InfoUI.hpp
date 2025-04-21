#ifndef INFOUI_HPP
#define INFOUI_HPP

/**
 * @file InfoUI.hpp
 * @brief Declares the InfoPage class responsible for showing the help/instructions screen.
 */

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"

using namespace sf;

/**
 * @class InfoPage
 * @brief Manages the display and interaction of the information page (manual and credits).
 */
class InfoPage {
public:
    /**
     * @brief Constructs the InfoPage and initializes buttons and textures.
     */
    InfoPage();  // Constructor
    /**
     * @brief Handles user input on the info page, including returning to the main menu.
     * @param window The SFML render window.
     * @param event SFML event object.
     * @param backToMenu Flag indicating whether to return to the main menu.
     */
    void handleEvent(RenderWindow& window, Event& event, bool& backToMenu);
    /**
     * @brief Draws all elements of the info page.
     * @param window The SFML render window.
     */
    void draw(RenderWindow& window);  // Dibuja los elementos
    /**
     * @brief Reloads or resets the textures (e.g., when switching views).
     */
    void reset();  // Recarga las texturas

private:
    Texture manualTexture;   ///< Texture for the manual screen
    Texture creditsTexture;  ///< Texture for the credits screen
    Sprite backgroundSprite; ///< Background sprite for the info page
    Button backButton;       ///< Button to return to the main menu
    Button manualButton;     ///< Button to show instructions
    Button creditsButton;    ///< Button to show credits
};

#endif // INFOUI_HPP

