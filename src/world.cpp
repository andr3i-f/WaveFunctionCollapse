#include "world.hpp"

World::World() {
  window.create(sf::VideoMode({800, 800}), "WCF");
}

World::~World() {

}

void World::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void World::update() {

}

void World::render() {

}

void World::processEvents() {
  while (const auto event = window.pollEvent()) {
    if (event.is<sf::Event::Closed>()) {
      window.close();
    }
  }
}