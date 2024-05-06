#pragma once

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(sf::Texture &, sf::Font &, sf::Vector2f, int, int, int);
    Tile(Tile &);
    ~Tile();

    bool isTransformed();
    void updatePossibilities();
    void transform();

    void draw(sf::RenderWindow&);
private:
    sf::Sprite sprite;
    sf::Texture texture;

    sf::Font font;
    sf::Text text;
    int possibilities{};

    int x{}, y{};

    bool transformed{};
};