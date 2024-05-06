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