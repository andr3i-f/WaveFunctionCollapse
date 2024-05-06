#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <iostream>
#include "tile.hpp"

class World {
public:
    World();
    ~World();

    void run();
    void update();
    void render();
    void processEvents();
private:
    uint SCREEN_WIDTH{ 800 };
    uint SCREEN_HEIGHT{ 800 };
    int AMOUNT_OF_TILES{ 50 };
    int TILE_POSSIBILITIES{ 7 };

    sf::Texture texture;
    sf::Font font;

    sf::RenderWindow window;
    std::array<std::array<std::unique_ptr<Tile>, 50>, 50> array;
};