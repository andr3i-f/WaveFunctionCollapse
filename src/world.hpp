#pragma once

#include <SFML/Graphics.hpp>
#include <array>
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
    int SCREEN_WIDTH{ 800 };
    int SCREEN_HEIGHT{ 800 };

    sf::RenderWindow window;
    std::array<std::array<Tile, 32>, 32> array;
};