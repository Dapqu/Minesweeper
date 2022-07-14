#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
using namespace sf;

class Tile {
    // Every tile will have 4 boolean variable
    // Is the game in Debug mode
    // Is this tile a mine
    // Is this tile revealed by player (left click)
    bool isDebugged;
    bool isMine;
    bool isRevealed;

    // How many mines are next to this tile (8 tiles)
    // xxx
    // xox
    // xxx
    unsigned int nearByMineCount;

    // Storage for tile used sprites, including:
    // Background tile: tile_revealed
    // Cover tile: tile_hidden
    // Flag tile: flag
    // Icon tile: mine, number, or nothing
    map<String, Sprite> tileSprites;
public:
    // Is this tile flagged by player (right click)
    bool isFlagged;

    // A vector that stores pointers that point to the 8 adjacent tiles
    vector<Tile*> adjacentTiles;

    Tile(float x, float y, map<string, Texture> &textures);
    void DefineTile(map<string, Texture> &textures);
    void LeftClick(int &tileRevealed);
    void RightClick();
    void Debug();
    void DrawTile(RenderWindow &window);
    void SetMine(bool isMine);
    void ResetStats();

    /*********** Getters ***********/
    bool GetIsDebugged() const;
    bool GetIsMine() const;
    bool GetIsFlagged() const;
    bool GetIsRevealed() const;
    unsigned int GetNearByMineCount() const;
    map<String, Sprite> GetSprites();
};