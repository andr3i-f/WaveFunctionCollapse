#include "world.hpp"

World::World() {
  if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    std::cerr << "Could not load font 'arial.ttf'" << std::endl;
  }
  if (!texture.loadFromFile("assets/images/wcf_pixel_sheet.png")) {
    std::cerr << "Could not load image 'wcf_pixel_sheet.png'" << std::endl;
  }

  window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "WCF");
}

World::~World() { }

void World::run() {
  uint tileWidth{ SCREEN_WIDTH / AMOUNT_OF_TILES }; // Should just make this into one variable
  uint tileHeight{ SCREEN_HEIGHT / AMOUNT_OF_TILES };

  for (size_t i{ 0 }; i < AMOUNT_OF_TILES; ++i) {
    for (size_t j{ 0 }; j < AMOUNT_OF_TILES; ++j) {
      sf::Vector2f position{tileWidth/2 + (float)i * tileWidth, tileHeight/2 + (float)j * tileHeight };
      array[i][j] = std::make_unique<Tile>(texture, font, position, TILE_POSSIBILITIES, i, j);
    }
  }

  while (window.isOpen()) {
    processEvents();
    update();
    collapse();
    render();
  }
}

void World::update() {

}

void World::render() {
  window.clear();

  for (size_t i{ 0 }; i < AMOUNT_OF_TILES; ++i) {
    for (size_t j{ 0 }; j < AMOUNT_OF_TILES; ++j) {
      array[i][j]->draw(window);
    }
  }

  window.display();
}

void World::processEvents() {
  while (const auto event = window.pollEvent()) {
    if (event.is<sf::Event::Closed>()) {
      window.close();
    }
  }
}

void World::collapse() {
  sf::Vector2i tilePosition{findTile()};
  array[tilePosition.x][tilePosition.y]->transform();
  std::stack<TilePositionDirection> stack;
  getNeighbors(stack, tilePosition);

  while (!stack.empty()) {
    TilePositionDirection current{ stack.top() };
    stack.pop();
    array[current.x][current.y]->updatePossibilities(key, array[tilePosition.x][tilePosition.y], current.d);
  }
}

sf::Vector2i World::findTile() {
  // Find the tile with the smallest entropy value - picks random tile in beginning
  std::random_device rd;
  std::uniform_int_distribution<std::mt19937::result_type> range(0, AMOUNT_OF_TILES - 1);
  int x{ 0 }, y{ 0 };
  int lowestEntropyValue{ TILE_POSSIBILITIES };

  for (size_t i{ 0 }; i < AMOUNT_OF_TILES; ++i) {
    for (size_t j{ 0 }; j < AMOUNT_OF_TILES; ++j) {
      if (array[i][j]->getEntropyLevel() < lowestEntropyValue) {
        x = i;
        y = j;
        lowestEntropyValue = array[i][j]->getEntropyLevel();
      }
    }
  }

  sf::Vector2i randomXY = {static_cast<int>(range(rd)), static_cast<int>(range(rd))};
  sf::Vector2i tileXY = {x, y};

  return lowestEntropyValue == TILE_POSSIBILITIES ? randomXY : tileXY;
}

void World::getNeighbors(std::stack<TilePositionDirection> & stack, sf::Vector2i & tilePosition) {
  for (int x{ -1 }; x < 2; ++x) {
    for (int y{ -1 }; y < 2; ++y) {
      try {
        if ((x == 0 || y == 0) && (x != 0 || y != 0)) {
          if (array.at(x + tilePosition.x).at(y + tilePosition.y)) {
            Direction d;
            if (x == 0 && y == -1) {
              d = N;
            } else if (x == -1 && y == 0) {
              d = W;
            } else if (x == 1 && y == 0) {
              d = E;
            } else if (x == 0 && y == 1) {
              d = S;
            }
            stack.push({x + tilePosition.x, y + tilePosition.y, d});
          }
        }
      } catch (std::out_of_range & e) { }
    }
  }
}