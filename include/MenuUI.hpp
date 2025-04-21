#ifndef MENUUI_HPP
#define MENUUI_HPP

/**
 * @file MenuUI.hpp
 * @brief Declares the Menu class for handling the game's main menu interface.
 */

 #include <SFML/Graphics.hpp>
 #include "ButtonUI.hpp"
 #include "InfoUI.hpp"
 
 using namespace sf;
 
 /**
  * @class Menu
  * @brief Represents the main menu of the game, including navigation to play and info screens.
  */
 class Menu {
 public:
     /**
      * @brief Constructs the main menu, initializing buttons and textures.
      */
     Menu();
 
     /**
      * @brief Handles input events for the menu, such as clicking buttons.
      * @param window The SFML render window.
      * @param event The event to process.
      * @param isPlaying Set to true if the play button is clicked.
      * @param backToMenu Used to return from the info page to the menu.
      */
     void handleEvent(RenderWindow& window, Event& event, bool& isPlaying, bool& backToMenu);
 
     /**
      * @brief Draws the menu and its buttons on the window.
      * @param window The SFML render window.
      */
     void draw(RenderWindow& window);
 
 private:
     Button playButton;           ///< Button to start the game
     Button infoButton;           ///< Button to go to the information screen
     Button exitButton;           ///< Button to exit the game
     InfoPage info;               ///< InfoPage instance for help/instructions
     Texture backgroundTexture;   ///< Texture for the menu background
     Sprite backgroundSprite;     ///< Sprite to render the background
     bool inInfoPage;             ///< Flag to determine if currently in the info page
 };
 
 #endif // MENUUI_HPP