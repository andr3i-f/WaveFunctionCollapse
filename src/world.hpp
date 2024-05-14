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
    std::unordered_map<TileType, std::array<TileType, 4>> key {
            {grass,{grass, grass, grass, grass}},
            {grassSandHalfN, {water, grassSandHalfN, grass, grassSandHalfN}},
            {grassSandHalfE, {grassSandHalfE, water, grassSandHalfE, grass}},
            {grassSandHalfS, {grass, grassSandHalfS, water, grassSandHalfS}},
            {grassSandHalfW, {grassSandHalfW, grass, grassSandHalfW, water}},
            {grassSandCornerNE, {grassSandHalfE, grassSandHalfN, grass, grass}},
            {grassSandCornerSE, {grass, grassSandHalfS, grassSandHalfE, grass}},
            {grassSandCornerSW, {grass, grass, grassSandHalfW, grassSandHalfS}},
            {grassSandCornerNW, {grassSandHalfW, grass, grass, grassSandHalfN}},
            {water, {water, water, water, water}}
    };
};