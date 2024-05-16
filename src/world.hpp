#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <random>
#include "tile.hpp"

struct TilePositionDirection {
  TilePositionDirection(int x, int y, Direction d) : x(x), y(y) {
    this->d = d;
  }
  int x{}, y{};
  Direction d;
};

class World {
public:
    World();
    ~World();

    void run();
    void update();
    void render();
    void processEvents();

    void collapse();
    sf::Vector2i findTile();
    void getNeighbors(std::stack<TilePositionDirection>&, sf::Vector2i&);
private:
    uint SCREEN_WIDTH{ 800 };
    uint SCREEN_HEIGHT{ 800 };
    int AMOUNT_OF_TILES{ 50 };
    int TILE_POSSIBILITIES{ 9 };

    sf::Texture texture;
    sf::Font font;

    sf::RenderWindow window;
    std::array<std::array<std::unique_ptr<Tile>, 50>, 50> array;

    // Key - [N, E, S, W]
    // Tile Connections Values - [ grass connection : 0, water connection : 1, water/grass : 2-5 (dependent on direction)]
    std::unordered_map<TileType, std::array<int, 4>> key {
            {grass,{0, 0, 0, 0}},
            {grassSandHalfN, {1, 2, 0, 2}},
            {grassSandHalfE, {3, 1, 3, 0}},
            {grassSandHalfS, {0, 4, 1, 4}},
            {grassSandHalfW, {5, 0, 5, 1}},
            {grassSandCornerNE, {3, 2, 0, 0}},
            {grassSandCornerSE, {0, 4, 3, 0}},
            {grassSandCornerSW, {0, 0, 5, 4}},
            {grassSandCornerNW, {5, 0, 0, 2}},
            {water, {1, 1, 1, 1}}
    };
};