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

void Tile::updatePossibilities(std::unordered_map<TileType, std::array<TileType, 4>> & key, TileType & otherType, Direction & otherDirection) {
  for (auto it{ possibleTiles.begin() }; it != possibleTiles.end(); ++it) {
    bool found{ false };

    for (const auto & [k, v] : key) {
      if (v[otherDirection] == *it) { found = true; }
    }

    if (!found) {
      it = possibleTiles.erase(it);
    }
  }
}

void Tile::transform() {
  transformed = true;
  std::random_device rd;
  std::uniform_int_distribution<std::mt19937::result_type> range(0, possibleTiles.size() - 1);

  switch (possibleTiles[range(rd)]) {
    case grass:
      type = grass;
      sprite.setTextureRect(sf::IntRect{{0, 0}, {16, 16}});
      break;
    case grassSandHalfN:
      sprite.setTextureRect(sf::IntRect{{0, 64}, {16, 16}});
      break;
    case grassSandHalfE:
      sprite.setTextureRect(sf::IntRect{{0, 48}, {16, 16}});
      break;
    case grassSandHalfS:
      sprite.setTextureRect(sf::IntRect{{16, 64}, {16, 16}});
      break;
    case grassSandHalfW:
      sprite.setTextureRect(sf::IntRect{{16, 48}, {16, 16}});
      break;
    case grassSandCornerNE:
      sprite.setTextureRect(sf::IntRect{{32, 16}, {16, 16}});
      break;
    case grassSandCornerSE:
      sprite.setTextureRect(sf::IntRect{{48, 16}, {16, 16}});
      break;
    case grassSandCornerSW:
      sprite.setTextureRect(sf::IntRect{{48, 0}, {16, 16}});
      break;
    case grassSandCornerNW:
      sprite.setTextureRect(sf::IntRect{{32, 0}, {16, 16}});
      break;
    case water:
      sprite.setTextureRect(sf::IntRect{{0, 32}, {16, 16}});
      break;
    default:
      break;
  }
}

bool Tile::isTransformed() {
  return transformed;
}

void Tile::draw(sf::RenderWindow & window) {
  !transformed ? window.draw(text) : window.draw(sprite);
}