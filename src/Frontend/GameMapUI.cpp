#include "GameMapUI.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>



GameMap::GameMap():
  buyButton(Vector2f(610, 400), "assets/img/buy.png", Vector2f(75, 50)),
  leftBuyButton(Vector2f(530, 400), "assets/img/left.png", Vector2f(75, 50)),
  rightBuyButton(Vector2f(690, 400), "assets/img/right.png", Vector2f(75, 50)),
  selectedButton(Vector2f(200, 650), "assets/img/buy.png", Vector2f(75, 50)),
  leftShipButton(Vector2f(100, 650), "assets/img/left.png", Vector2f(75, 50)),
  rightShipButton(Vector2f(300, 650), "assets/img/right.png", Vector2f(75, 50))
{
  shipTextures.resize(6);
  shipSprites.resize(6);
  cost.resize(6);
  cost[0] = "Price: $100";
  cost[1] = "Price: $200";
  cost[2] = "Price: $300";
  cost[3] = "Price: $400";
  cost[4] = "Price: $500";
  cost[5] = "Price: $600";
  if (!shipTextures[0].loadFromFile("assets/img/ship.png")) {
    std::cerr << "Error loading ship texture" << std::endl;
  }
  shipTextures[1].loadFromFile("assets/img/shipGuerra.png");
  shipTextures[2].loadFromFile("assets/img/shipPirate.png");
  shipTextures[3].loadFromFile("assets/img/shipOnePiece.png");
  shipTextures[4].loadFromFile("assets/img/shipEnd.png");
  shipTextures[5].loadFromFile("assets/img/shipMoon.png");

  for (int i = 0; i < 6; ++i) {
    shipSprites[i].setTexture(shipTextures[i]);
    shipSprites[i].setPosition(590, 250);
  }

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
if (!explosionTexture.loadFromFile("assets/img/smoke.png")) {
    std::cerr << "Error loading explosion texture" << std::endl;
    // manejar error
  }
  explosionSprite.setTexture(explosionTexture);
  infoText.setFont(font);
  backgroundSprite.setTexture(backgroundTexture);

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      board[i][j] = WATER;
    }
  }

  //if (!hitTexture.loadFromFile("explosion.png")) return false;
}

void GameMap::printText(RenderWindow& window, const std::string& text, int x,
      int y) {
  infoText.setString(text);
  infoText.setCharacterSize(50);
  infoText.setFillColor(Color::Black);
  infoText.setStyle(Text::Bold);
  infoText.setPosition(x, y);
  window.draw(infoText);
}

void GameMap::smokeExplosion(RenderWindow& window, int x, int y) {
  explosionSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
  explosionSprite.setScale(
      (float)CELL_SIZE / explosionTexture.getSize().x,
      (float)CELL_SIZE / explosionTexture.getSize().y
  );
  window.draw(explosionSprite);
}

void GameMap::render(RenderWindow& window) {
  // Draw background
  window.clear(sf::Color::Blue);
  draw(window);
  drawShips(window);
  rightBuyButton.draw(window);
  leftBuyButton.draw(window);
  buyButton.draw(window);
  selectedButton.draw(window);
  leftShipButton.draw(window);
  rightShipButton.draw(window);
  printText(window, "0", 575, 5);
  printText(window, "0", 615, 85);
  printText(window, "0", 615, 160);
  printText(window, cost[Ship], 540, 350);
  window.draw(shipSprites[Ship]);
  selectedButtonAction(window);
  window.display();
}
void GameMap::drawShips(RenderWindow& window) {
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      int shipType = board[row][col];
      if (shipType >= 0 && shipType < 6) {
        Sprite shipSprite(shipTextures[shipType]);
        shipSprite.setScale(
          (float)CELL_SIZE / shipTextures[shipType].getSize().x,
          (float)CELL_SIZE / shipTextures[shipType].getSize().y
        );
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
    board[r][c] = Ship;
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
    }else if(buyButton.isMouseOver(window)) {
    } else if(leftBuyButton.isMouseOver(window)) {
      Ship= (Ship - 1) % 6;
      if (Ship < 0) {
        Ship = 5;
      }
    } else if(rightBuyButton.isMouseOver(window)) {
      Ship= (Ship + 1) % 6;
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

void GameMap::selectedButtonAction(RenderWindow& window) {
  // Implementar la acción del botón seleccionado
  // Por ejemplo, cambiar el color del botón o realizar alguna acción
  Sprite shipSprite = shipSprites[Ship];
  shipSprite.setPosition(180, 500);
  window.draw(shipSprite);
}