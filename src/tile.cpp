#include "tile.hpp"

Tile::Tile(sf::Texture & t, sf::Font & f, int p) : sprite(t), text(f), possibilities(p), transformed(false) { }

Tile::~Tile() { }

void Tile::updatePossibilities() {

}

void Tile::transform() {

}

bool Tile::isTransformed() {
  return transformed;
}

void Tile::draw(sf::RenderWindow & window) {
  window.draw(sprite);
}