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
  buyPointsButton(Vector2f(620, 620), "assets/img/buy.png", Vector2f(75, 50))
{
  // Game game(10, 10, 5, 100);
  player1 = new Player(GRID_SIZE, GRID_SIZE);
  player2 = new Player(GRID_SIZE, GRID_SIZE);
  player1->placeShips(NUM_SHIPS+1, -1);
  player2->placeShips(NUM_SHIPS+1, -1);
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
      int y, const sf::Color color) {
  infoText.setString(text);
  infoText.setCharacterSize(50);
  infoText.setFillColor(color);
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
  if(isShipPlaced(x, y, player2->getboard())) {
    explosionSprite.setColor(Color::Red);
  } else if(isShipPlaced(x, y, player2->getboard())) {
    explosionSprite.setColor(Color::Green);
  } else {
    explosionSprite.setColor(Color::White);
  }
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
  buyPointsButton.draw(window);
  printText(window, to_string(currency), 575, 5, sf::Color::Black);
  printText(window, to_string(shipCount), 615, 85, sf::Color::Black);
  printText(window, "0", 615, 160, sf::Color::Black);
  printText(window, cost[buyShip], 540, 350, sf::Color::Black);
  printText(window, "Y:"+to_string(xCord), 440, 500, sf::Color::Black);
  printText(window, "X:"+to_string(yCord), 340, 500, sf::Color::Black);
  printText(window, "Actions:"+to_string(getAction()), 340, 580, sf::Color::Black);
  printText(window, "Points:"+to_string(improvementPoints), 340, 650, sf::Color::Black);
  selectedMode(window);
  window.draw(shipSprites[buyShip]);
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
  player1->setaction(TURNS);
  player2->setaction(TURNS);
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
      if (playerTurn == true) {
        shipCount = player2->getShips().size();
        currency = player1->getMoney();
        improvementPoints = player1->getImprovementPoints();
        updateMatrix(player1->getChangeMatrix());
      }
      if (playerTurn == false) {
        shipCount = player1->getShips().size();
        currency = player2->getMoney();
        player2->getImprovementPoints();
        updateMatrix(player2->getChangeMatrix());
      }
      // new game wait
      // cambio de jugador y pantalla en negro
      if (player1->getaction() == 0 && playerTurn) {
        blackScreen(window);
        reset();
        printf("Player 1 turn\n");
        playerTurn = false;  // pasa a jugador 2
        player2->setaction(TURNS);  // solo jugador 2 recibe nuevos turnos
      }
      else if (player2->getaction() == 0 && !playerTurn) {
        blackScreen(window);
        reset();
        printf("Player 2 turn\n");
        playerTurn = true;   // pasa a jugador 1
        player1->setaction(TURNS);  // solo jugador 1 recibe nuevos turnos
      }
      // Cambio de turno
      if(playerTurn){
        // printf("Player 1 turn\n");
        // updateMatrix();
      } else {
        // printf("Player 2 turn\n");
        // updateMatrix();
      }
      if (player1->allShipsSunk() && player1->isShipempty()) {
        printf("Player 1 wins\n");
        endRound = true;
      }
      if (player2->allShipsSunk() && player2->isShipempty()) {
        printf("Player 2 wins\n");
        endRound = true;
      }
      if(event.type == Event::Closed) {
        endRound = true;
        window.close();
      }

      if(attack) {
        // Si el jugador ataca, se muestra la matriz de ataque
        player1->attackMatrix();
        player2->attackMatrix();
      }else{
        // Si el jugador no ataca, se muestra la matriz de barcos
        player1->setPlayerBoard();
        player2->setPlayerBoard();
      }
    }
    window.close();
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
  changePlayer=true;
  sf::sleep(sf::seconds(1));
  window.clear(sf::Color::Black);
  window.display();
  sf::sleep(sf::seconds(5));
  player1->setaction(TURNS);
  player2->setaction(TURNS);
  changePlayer=false;
}

void GameMap::handleEvent(RenderWindow& window, Event& event) {
  if (event.type == Event::Closed) {
    window.close();
    return;
  }

  if (event.type == Event::MouseButtonPressed) {
    int col = event.mouseButton.x / CELL_SIZE;
    int row = event.mouseButton.y / CELL_SIZE;

    if (event.mouseButton.x >= 0 && event.mouseButton.x <= GRID_SIZE * CELL_SIZE &&
        event.mouseButton.y >= 0 && event.mouseButton.y <= GRID_SIZE * CELL_SIZE) {
      handleGridClick(row, col, event.mouseButton.button);
    } else {
      if(player1->isShipempty() && player2->isShipempty() and currency > 0) {
        handleBuyActions(window);
      }
      
    }
  } else if (event.type == Event::KeyPressed) {
    handleKeyInput(event.key.code);
  }
}

void GameMap::handleGridClick(int row, int col, Mouse::Button button) {
  if (button == Mouse::Left) {
    handleLeftClick(row, col);
  } else if (button == Mouse::Right) {
    handleRightClick(row, col);
  }
}

void GameMap::handleLeftClick(int row, int col) {
  if (canAttack()) {
    int damage;
    if (playerTurn) {
      damage = player1->getShipDamage(xCord, yCord);
      player2->displayOwnBoard();
    } else {
      player1->displayOwnBoard();
      damage = player2->getShipDamage(xCord, yCord);
    }
    if (damage == -1) {
      printf("No hay barcos en esa posición\n");
    } else  {
      if (playerTurn) {
        
        player2->receiveShot(row, col, damage);
        player1->setLessAction();
        printf("Actions: %d\n", player1->getaction());
        updateMatrix(player1->getChangeMatrix());
        player1->plusMoney(INCREMENT);
        
      } else {
        
        player1->receiveShot(row, col, damage);
        player2->setLessAction();
        printf("Actions: %d\n", player2->getaction());
        updateMatrix(player2->getChangeMatrix());
        player2->plusMoney(INCREMENT);
        
      }
    }
    printf("Atacar\n");
    // attackShip(row, col);

  } else {
    // Coloca un barco
    if (canPutShip(player1, row, col, playerTurn)) {
      addShipStorage(row, col, player1);
      player1->setPlayerBoard();
      updateMatrix(player1->getChangeMatrix());
      player1->setLessAction();
      player1->displayOwnBoard();
    } else if(canPutShip(player2, row, col, !playerTurn)) {
      addShipStorage(row, col, player2);
      player2->setPlayerBoard();
      updateMatrix(player2->getChangeMatrix());
      player2->setLessAction();
      printf("Actions Player 2: %d\n", player2->getaction());
      player2->displayOwnBoard();
    }
    // printf("poner barco");
    // placeShip(row, col, shipSize, horizontal);
  }
}

void GameMap::handleRightClick(int row, int col) {
  // Remove ship
  if (!selected){
    if (playerTurn && isShipPlaced(row, col, player1->getboard())) {
      removeShip(row, col, player1);
      //player1->setLessAction();
      player1->plusMoney(INCREMENT);
      player1->displayOwnBoard();
      updateMatrix(player1->getChangeMatrix());
    } else if(isShipPlaced(row, col, player2->getboard())) {
      removeShip(row, col, player2);
      //player2->setLessAction();
      player2->plusMoney(INCREMENT);
      player2->displayOwnBoard();
      updateMatrix(player2->getChangeMatrix());
    }else {
      printf("No hay barcos en esa posición\n");
    }
  } else {
    // Select ship
    // Verificar si hay un barco en la posicion
    if (playerTurn) {
      if(isShipPlaced(row, col, player1->getboard())) {
        // coordenadas del barco que ataca
        xCord = row;
        yCord = col;      
      }
    } else {
      if(isShipPlaced(row, col, player2->getboard())) {
        // coordenadas del barco que ataca
        xCord = row;
        yCord = col;      
      }
    }
  }
}

void GameMap::handleBuyActions(RenderWindow& window) {
  if(buyButton.isMouseOver(window)) {
    // comprar barco
    // Ship contiene numero el barco a comprar
    if(playerTurn) {
      buyShips(player1);
      printf("Actions Player 1: %d\n", player1->getaction());
      selectedShip = buyShip;
      updateMatrix(player1->getChangeMatrix());
    } else {
      buyShips(player2);
      printf("Actions Player 2: %d\n", player2->getaction());
      selectedShip = buyShip;
      updateMatrix(player2->getChangeMatrix());
    }
  } else if(leftBuyButton.isMouseOver(window)) {
    buyShip= (buyShip - 1) % 6;
    if (buyShip < 0) {
      buyShip = 5;
    }
  } else if(rightBuyButton.isMouseOver(window)) {
    buyShip= (buyShip + 1) % 6;
  }else if(buyPointsButton.isMouseOver(window)) {
    // comprar puntos de mejora
    if(playerTurn) {
      player1->plusImprovementPoints();
      player1->lessMoney(100);
      player1->setLessAction();
      printf("Actions Player 1: %d\n", player1->getaction());
      updateMatrix(player1->getChangeMatrix());
    } else {
      player2->plusImprovementPoints();
      player2->lessMoney(100);
      player2->setLessAction();
      printf("Actions Player 2: %d\n", player2->getaction());
      updateMatrix(player2->getChangeMatrix());
    }
    printf("Buy points\n");
  }
}

void GameMap::handleKeyInput(Keyboard::Key key) {
  if (key == Keyboard::A) {
    attack = !attack;
  } else if (key == Keyboard::S) {
    selected = !selected;
  }
}

void GameMap::removeShip(int row, int col, Player* player) {
  // Comprueba si el jugador tiene barcos en el storage
  if (player->isShipempty()) {
      auto &ships = player->getShips();  // Referencia al vector interno de barcos
      // Recorre cada barco para encontrar el que ocupa la celda (row, col)
      for (size_t i = 0; i < ships.size(); ++i) {
          if (ships[i].occupies(row, col)) {
              player->setShipStorage(ships[i]);             // Guarda el barco seleccionado
              ships.erase(ships.begin() + i);                // Lo elimina del vector
              player->getboard()[row][col] = WATER;          // Marca la celda como agua
              return;                                        // Sale tras eliminar el barco
          }
      }
  }
  // Si no hay barcos o no se encontró ninguno, no realiza ninguna acción
}

void GameMap::addShipStorage(int row, int col, Player* player) {
  // Solo actúa si hay un barco previamente guardado en el storage
  if (!player->isShipempty()) {
      auto ship = player->getShipStorage();  // Obtiene el barco del storage
      // Coloca el barco en la celda (row, col) y actualiza el tablero
      player->getboard()[row][col] = ship.getLevel();
      ship.setPosition(row, col);  // Actualiza la posición del barco
      player->getShips().push_back(ship);  // Agrega el barco al vector de barcos del jugador
      player->setShipStorageEmpty();  // Marca el storage como vacío
  }
}
void GameMap::draw(RenderWindow& window) {
  // Draw background
  window.draw(backgroundSprite);
}

void GameMap::selectedButtonAction(RenderWindow& window) {
  // Implementar la acción del botón seleccionado
  // Por ejemplo, cambiar el color del botón o realizar alguna acción
  if(selectedShip != -1 && (!player1->isShipempty() || !player2->isShipempty())) {
    Sprite shipSprite = shipSprites[selectedShip];
    shipSprite.setPosition(150, 550);
    window.draw(shipSprite);
  }else{
    selectedShip = -1;
  }
}

bool GameMap::isShipPlaced(int x, int y, int** board) {
  return board[x][y] != WATER;
}

void GameMap::reset() {
  attack = false;
  selected = false;
  yCord = -1;
  xCord = -1;
}

int GameMap::getAction() {
  if(playerTurn) {
    return player1->getaction();
  } else {
    return player2->getaction();
  }
}

void GameMap::buyShips(Player* player) {
    Ship ship = Ship(1, 1, 3, 1, buyShip);
    player->setShipStorage(ship);
    player->lessMoney(100 * (buyShip + 1));
}

bool GameMap::canAttack() {
 
  return ((attack) && (player1->isShipempty() && player2->isShipempty()) &&
      (xCord!= -1 && yCord != -1));
}

bool GameMap::canPutShip(Player* player, int row, int col, bool turn) {
  return ((turn) && (!isShipPlaced(row, col, player->getboard())) &&
  (!player->isShipempty()) && !attack);
}

void GameMap::freeMemory() {
  if (player1 != nullptr) {
    delete player1;
    player1 = nullptr;
  }
  if (player2 != nullptr) {
    delete player2;
    player2 = nullptr;
  }
  // Limpiar recursos gráficos si es necesario
  shipTextures.clear();
  shipSprites.clear();
  cost.clear();

  std::cout << "Memoria liberada correctamente." << std::endl;
}

void GameMap::selectedMode(RenderWindow &window){
  if(attack){
    printText(window, "Attack", 10, 500, sf::Color::Red);
  }else{
    printText(window, "Put", 10, 500, sf::Color::Red);
  }

  if(selected){
    printText(window, "Select", 10, 530, sf::Color::Red);
  }else{
    printText(window, "Remove", 10, 530, sf::Color::Red);
  }
}