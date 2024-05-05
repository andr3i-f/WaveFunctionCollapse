#pragma once

#include <SFML/Graphics.hpp>

class World {
public:
    World();
    ~World();

    void run();
    void update();
    void render();
    void processEvents();
private:
    sf::RenderWindow window;
};