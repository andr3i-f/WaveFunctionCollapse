#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

enum TileType {
    none = 0,
    grass,
    grassSandHalfN,
    grassSandHalfE,
    grassSandHalfS,
    grassSandHalfW,
    grassSandCornerNE,
    grassSandCornerSE,
    grassSandCornerSW,
    grassSandCornerNW,
    water
};

enum Direction {
    N = 0,
    E,
    S,
    W
};

class Tile {
public:
    Tile(sf::Texture &, sf::Font &, sf::Vector2f, int, int, int);
    Tile(Tile &);
    ~Tile();

    bool isTransformed();
    void updatePossibilities(std::unordered_map<TileType, std::array<TileType, 4>> &, std::unique_ptr<Tile> &, Direction &);
    void transform();

    void draw(sf::RenderWindow&);
    int getEntropyLevel();
    std::vector<TileType>& getPossibleTiles();

    int getX();
    int getY();
private:
    void eraseTileType(TileType);

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Font font;
    sf::Text text;

    int possibilities{};
    int x{}, y{};
    TileType type{ none };
    bool transformed{};

    std::vector<TileType> possibleTiles{grass, grassSandHalfN, grassSandHalfE, grassSandHalfS,
                                           grassSandHalfW, grassSandCornerNE, grassSandCornerSE,
                                           grassSandCornerSW, grassSandCornerNW, water};
};