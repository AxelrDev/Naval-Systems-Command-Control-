#include "GameMapUI.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>



GameMap::GameMap(){
  if (!shipTexture.loadFromFile("assets/img/ship.png")) {
    std::cerr << "Error loading ship texture" << std::endl;
  }

  if (!backgroundTexture.loadFromFile("assets/img/board.png")) {
    std::cerr << "Error loading ship texture" << std::endl;
  }

  if (!font.loadFromFile("assets/font/Arcade.ttf")) {
    std::cerr << "Error loading font" << std::endl;
    // manejar error
}
  infoText.setFont(font);
  backgroundSprite.setTexture(backgroundTexture);

  //if (!hitTexture.loadFromFile("explosion.png")) return false;
}

void GameMap::printText(RenderWindow& window, const std::string& text, int x,
      int y) {
  infoText.setString(text);
  infoText.setCharacterSize(24);
  infoText.setFillColor(Color::Black);
  infoText.setStyle(Text::Bold);
  infoText.setPosition(x, y);
  window.draw(infoText);
}

void GameMap::render(RenderWindow& window) {
  // Draw background
  window.clear(sf::Color::Blue);
  draw(window);
  drawShips(window);
  printText(window, "0", 575, 10);
  printText(window, "5", 575, 30);
  window.display();
}
void GameMap::drawShips(RenderWindow& window) {
  Sprite shipSprite(shipTexture);
  shipSprite.setScale(
      (float)CELL_SIZE / shipTexture.getSize().x,
      (float)CELL_SIZE / shipTexture.getSize().y
  );

  for (int row = 0; row < GRID_SIZE; ++row) {
      for (int col = 0; col < GRID_SIZE; ++col) {
          if (board[row][col] == SHIP) {
              shipSprite.setPosition(col * CELL_SIZE, row * CELL_SIZE);
              window.draw(shipSprite);
          }
      }
  }
}

void GameMap::updateMatrix(int **matrix) {
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
        board[row][col] = matrix[row][col];
    }
  }
}


void GameMap::drawGrid(RenderWindow& window) {
    // Draw grid
  for (int i = 0; i < GRID_SIZE; i++) {
    Vertex line[] = { Vertex(Vector2f(i*CELL_SIZE, 0), Color::White),
        Vertex(Vector2f(i*CELL_SIZE, GRID_SIZE*CELL_SIZE), Color::White) };
    window.draw(line, 2, Lines);
    Vertex line2[] = { Vertex(Vector2f(0, i*CELL_SIZE), Color::White),
        Vertex(Vector2f(GRID_SIZE*CELL_SIZE, i*CELL_SIZE), Color::White)};
    window.draw(line2, 2, Lines);
  }
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
      render(window);
      window.display();
      // new game wait     
    }
  }
}

void GameMap::attackShip(int row, int col) {
  if (board[row][col] == SHIP) board[row][col] = HIT;
}

void GameMap::placeShip(int row, int col, int size, bool horizontal) {
  for(int i = 0; i < size; i++) {
    int r = row + (horizontal ? 0 : i);
    int c = col + (horizontal ? i : 0);
    board[r][c] = SHIP;
  }
}

void GameMap::blackScreen(RenderWindow& window) {
  sf::sleep(sf::seconds(3));
  window.clear(sf::Color::Black);
  window.display();
  sf::sleep(sf::seconds(3));
}

void GameMap::handleEvent(RenderWindow& window, Event& event) {
  if (event.type == Event::Closed) {
    window.close();
  }
  if (event.type == Event::MouseButtonPressed) {
    // Get mouse position
    // Check if mouse is inside the grid
    if (event.mouseButton.x >= 0 && event.mouseButton.x <= GRID_SIZE*CELL_SIZE &&
        event.mouseButton.y >= 0 && event.mouseButton.y <= GRID_SIZE*CELL_SIZE) {
      int col = event.mouseButton.x / CELL_SIZE;
      int row = event.mouseButton.y / CELL_SIZE;
      if (event.mouseButton.button == Mouse::Left) {
        if (attack){
          attackShip(row, col);
        } else {
          placeShip(row, col, shipSize, horizontal);
        }
      }
      if (event.mouseButton.button == Mouse::Right) {
        // Remove ship
        int **matrix = new int*[GRID_SIZE];
        for (int i = 0; i < GRID_SIZE; ++i) {
          matrix[i] = new int[GRID_SIZE];
          for (int j = 0; j < GRID_SIZE; ++j) {
            matrix[i][j] = 0;
          }
        }
        matrix[1][1] = SHIP;
        updateMatrix(matrix);
        removeShip(row, col);
      }
    }
  }
}

void GameMap::removeShip(int row, int col) {
  printf("Removing ship at (%d, %d)\n", row, col);
  board[row][col] = WATER;
}

void GameMap::draw(RenderWindow& window) {
  // Draw background
  window.draw(backgroundSprite);
}

