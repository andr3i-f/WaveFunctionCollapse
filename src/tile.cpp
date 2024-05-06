#include "tile.hpp"

Tile::Tile(sf::Texture & t, sf::Font & f, sf::Vector2f position, int p, int x, int y)
: sprite(t), text(f), possibilities(p), transformed(false), x(x), y(y)
{
  sprite.setOrigin({8, 8});
  sprite.setPosition(position);
  text.setPosition(position);

  text.setStyle(sf::Text::Style::Regular);
  text.setCharacterSize(10);
  text.setString(std::to_string(possibilities));
}

Tile::Tile(Tile & other) : sprite(other.sprite), text(other.text) {
  possibilities = other.possibilities;
  transformed = false;
  x = other.x;
  y = other.y;
}

Tile::~Tile() = default;

void Tile::updatePossibilities() {

}

void Tile::transform() {
  transformed = true;
}

bool Tile::isTransformed() {
  return transformed;
}

void Tile::draw(sf::RenderWindow & window) {
  !transformed ? window.draw(text) : window.draw(sprite);
}