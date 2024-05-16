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

void Tile::updatePossibilities(std::unordered_map<TileType, std::array<int, 4>> & key, std::unique_ptr<Tile> & other, Direction & otherDirection) {
  std::vector<TileType> updatedPossibilities{};

  Direction oppositeDirection;

  if (otherDirection == N) {
    oppositeDirection = S;
  } else if (otherDirection == E) {
    oppositeDirection = W;
  } else if (otherDirection == S) {
    oppositeDirection = N;
  } else if (otherDirection == W) {
    oppositeDirection = E;
  }

  for (const TileType &t : other->getPossibleTiles()) {
    for (const auto & [k, v] : key) {
      if (v[oppositeDirection] == key[t][otherDirection]) {
        updatedPossibilities.emplace_back(k);
      }
    }
  }
  possibleTiles = updatedPossibilities;
  possibilities = possibleTiles.size();
  text.setString(std::to_string(possibilities));
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
      type = grassSandHalfN;
      sprite.setTextureRect(sf::IntRect{{0, 64}, {16, 16}});
      break;
    case grassSandHalfE:
      type = grassSandHalfN;
      sprite.setTextureRect(sf::IntRect{{0, 48}, {16, 16}});
      break;
    case grassSandHalfS:
      type = grassSandHalfS;
      sprite.setTextureRect(sf::IntRect{{16, 64}, {16, 16}});
      break;
    case grassSandHalfW:
      type = grassSandHalfW;
      sprite.setTextureRect(sf::IntRect{{16, 48}, {16, 16}});
      break;
    case grassSandCornerNE:
      type = grassSandCornerNE;
      sprite.setTextureRect(sf::IntRect{{32, 16}, {16, 16}});
      break;
    case grassSandCornerSE:
      type = grassSandCornerSE;
      sprite.setTextureRect(sf::IntRect{{48, 16}, {16, 16}});
      break;
    case grassSandCornerSW:
      type = grassSandCornerSW;
      sprite.setTextureRect(sf::IntRect{{48, 0}, {16, 16}});
      break;
    case grassSandCornerNW:
      type = grassSandCornerNW;
      sprite.setTextureRect(sf::IntRect{{32, 0}, {16, 16}});
      break;
    case water:
      type = water;
      sprite.setTextureRect(sf::IntRect{{0, 32}, {16, 16}});
      break;
    default:
      break;
  }
  possibilities = 10000000;
  possibleTiles.clear();
  possibleTiles.emplace_back(type);
}

bool Tile::isTransformed() {
  return transformed;
}

void Tile::draw(sf::RenderWindow & window) {
  !transformed ? window.draw(text) : window.draw(sprite);
}

int Tile::getEntropyLevel() {
  return possibilities;
}

std::vector<TileType>& Tile::getPossibleTiles() {
  return possibleTiles;
}

void Tile::eraseTileType(TileType t) {
  for (auto it{possibleTiles.begin()}; it != possibleTiles.end(); ++it) {
    if (*it == t) {
      possibleTiles.erase(it);
      break;
    }
  }
}

int Tile::getX() {
  return x;
}

int Tile::getY() {
  return y;
}