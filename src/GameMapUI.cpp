#include "GameMapUI.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>

GameMap::GameMap(){
    // Load background
    if (!backgroundTexture.loadFromFile("assets/img/background.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Center background
    //backgroundSprite.setPosition(Vector2f(35, 0));

}



void GameMap::run(RenderWindow& window) {
    bool endRound = false;
    
    while (window.isOpen()) {
        
        endRound = false;

        while (endRound == false) {
            Event event;
            while (window.pollEvent(event)) {
                this->handleEvent(window, event);
            }

            

            // Sprites draw
            window.clear();
            draw(window);
            window.display();

        // new game wait        
        
        }
    }
}

void GameMap::blackScreen(RenderWindow& window){
        window.clear(sf::Color::Black);
        window.display();
        sf::sleep(sf::seconds(3));
}


void GameMap::handleEvent(RenderWindow& window, Event& event) {
    if (event.type == Event::Closed) {
        window.close();
    }
    if (event.type == Event::KeyPressed) {
        blackScreen(window);
    }
}


void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}

