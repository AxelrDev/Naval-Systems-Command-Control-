/// @file GameMapUI.hpp
/// @brief Declara la clase GameMap que maneja la lógica de dibujo, interacción y renderizado del mapa de juego con barcos.
#include "GameMapUI.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>


/**
 * @brief Constructor de la clase GameMap.
 *
 * Inicializa botones, texturas, sprites, fuentes, y el tablero del juego.
 * Carga los recursos gráficos y define la posición inicial de cada elemento visual.
 */
GameMap::GameMap():
  buyButton(Vector2f(610, 400), "assets/img/buy.png", Vector2f(75, 50)),
  leftBuyButton(Vector2f(530, 400), "assets/img/left.png", Vector2f(75, 50)),
  rightBuyButton(Vector2f(690, 400), "assets/img/right.png", Vector2f(75, 50)),
  selectedButton(Vector2f(200, 650), "assets/img/selected.png", Vector2f(75, 50)),
  leftShipButton(Vector2f(100, 650), "assets/img/left.png", Vector2f(75, 50)),
  rightShipButton(Vector2f(300, 650), "assets/img/right.png", Vector2f(75, 50)),
  buyPointsButton(Vector2f(620, 620), "assets/img/buy.png", Vector2f(75, 50))
{
  Game game(10, 10, 5, 100);
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

  if (!improvementPointsTexture.loadFromFile("assets/img/points.png")) {
    std::cerr << "Error loading ship texture" << std::endl;
  }

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
  improvementPointsSprite.setTexture(improvementPointsTexture);
  improvementPointsSprite.setPosition(590, 500);

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
  buyPointsButton.draw(window);
  printText(window, to_string(currency), 575, 5);
  printText(window, "0", 615, 85);
  printText(window, "0", 615, 160);
  printText(window, cost[Ship], 540, 350);
  printText(window, "Y:"+to_string(xCord), 440, 500);
  printText(window, "X:"+to_string(yCord), 340, 500);
  window.draw(shipSprites[Ship]);
  selectedButtonAction(window);
  window.draw(improvementPointsSprite);
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
      // cambio de jugador y pantalla en negro
      if (movement == 0) {
        blackScreen(window);
        movement = 5;
        playerTurn = !playerTurn;
      }
      // Cambio de turno
      if(playerTurn){
        printf("Player turn\n");
        //updateMatrix();
      }  
    }
  }
}

void GameMap::attackShip(int row, int col) {
  if (board[row][col] != -1) board[row][col] = HIT;
  printf("Attacking ship at (%d, %d)\n", row, col);
}

void GameMap::placeShip(int row, int col, int size, bool horizontal) {
  for(int i = 0; i < size; i++) {
    int r = row + (horizontal ? 0 : i);
    int c = col + (horizontal ? i : 0);
    board[r][c] = selectedShip;
  }
}

void GameMap::blackScreen(RenderWindow& window) {
  sf::sleep(sf::seconds(1));
  window.clear(sf::Color::Black);
  window.display();
  sf::sleep(sf::seconds(5));
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
        // Ataca a los barcos
        if (attack){
          printf("Atacar");
          attackShip(row, col);
        } else {
          // Coloca un barco
          printf("poner barco");
          placeShip(row, col, shipSize, horizontal);
        }
      }
      if (event.mouseButton.button == Mouse::Right) {
        // Remove ship
        if (!selected){
          printf("Remove ship");
          // Remueve el barco
          removeShip(row, col);
          movement --;
        } else {
          // Select ship
          // Veridificar si hay un barco en la posicion
          if(isShipPlaced(row, col)) {
            // coordenadas del barco que ataca
            xCord = row;
            yCord = col;      
          }
        }
      }
    }else if(buyButton.isMouseOver(window)) {
      // comprar barco
      // Ship contiene numero el barco a comprar
      printf("Buy ship\n");
      movement --;
    } else if(leftBuyButton.isMouseOver(window)) {
      Ship= (Ship - 1) % 6;
      if (Ship < 0) {
        Ship = 5;
      }
    } else if(rightBuyButton.isMouseOver(window)) {
      Ship= (Ship + 1) % 6;
    }else if(leftShipButton.isMouseOver(window)) {
      previousSelection = (previousSelection - 1) % 6;
      if (previousSelection < 0) {
        previousSelection = 5;
      }
    } else if(rightShipButton.isMouseOver(window)) {
      previousSelection = (previousSelection + 1) % 6;
    } else if(selectedButton.isMouseOver(window)) {
      selectedShip = previousSelection;
      // coloca el barco seleccionado
      // selectedShip posee el barco seleccionado
      printf ("Selected ship: %d\n", selectedShip);
    }else if(buyPointsButton.isMouseOver(window)) {
      // comprar puntos de mejora
      printf("Buy points\n");
      movement --;
    }
  }else if(event.type==Event::KeyPressed) {
    // Si preseiona la letra A ataca barcos y pasa a una matriz sin barcos
    // Si presiona la letra S pasa a modo seleccion de barcos con click derecho
    if (event.key.code == Keyboard::A) {
      int **matrix= new int*[GRID_SIZE];
      for (int i = 0; i < GRID_SIZE; ++i) {
        matrix[i] = new int[GRID_SIZE];
      }
      for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
          matrix[i][j] = WATER;
        }
      }
      attack = true;
      updateMatrix(matrix);
    }else if(event.key.code == Keyboard::S) {
      selected = !selected;
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
  Sprite shipSprite = shipSprites[previousSelection];
  shipSprite.setPosition(180, 500);
  window.draw(shipSprite);
}

bool GameMap::isShipPlaced(int x, int y) {
  return board[x][y] != WATER;
}

void GameMap::reset() {
  attack = false;
  selected = false;
}