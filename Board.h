#pragma once
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>

using namespace std;
using namespace sf;

class Board {
    // simple enough, game is over or not
    bool gameOver;
    // won or lost
    bool lost;

    // read-in variable to store the value from config.cfg
    string noc;
    string nor;
    string mc;

    // then transform those 3 variable above into int using stoi()
    // Width of the window = numOfCols * 32
    unsigned int numOfCols;
    // Height of the window = numOfRows * 32 + 88
    unsigned int numOfRows;
    unsigned int mineCount;
    // TileCount = numOfCols * numOfRows
    unsigned int tileCount;
    // Tile that is shown, revealed.
    unsigned int tileShowed;
    unsigned int tileLeft;
    // Mine Count display on screen, can do negative
    int digitsMineCount;

    // Storage for all textures from images folder
    map<string, Texture> textures;
    // Storage for all board use sprites, including:
    // Digits: digits
    // faces: face_happy, face_lose, face_win
    // Debug: debug
    // Tests: test_1, test_2, test_3
    map<string, Sprite> boardSprite;
    // Digit Counter sprites
    map<int, Sprite> digitSprite;
    // a vector to store all the tiles on the board
    // vector size = tileCount = numOfCols * numOfRows
    vector<Tile> tiles;
    // a boolean vector to the true and false value of each tile, determine whether they are mine or not.
    vector<bool> isMines;

    // Testcases data vectors
    vector<bool> test1Mines;
    vector<bool> test2Mines;
    vector<bool> test3Mines;
public:
    Board();
    void ReadConfigFile();
    void SetMines();
    void Debug();
    void DrawBoard(RenderWindow &window);
    void CreateTiles();
    void LoadTextures();
    void UpdateFace();
    void AssignRandomMines();
    void UpdateGame(RenderWindow &window);
    void UpdateDigits();
    void LoadTest1();
    void LoadTest2();
    void LoadTest3();
    void LoadTests();
    void SetSpritesToTiles();

    void LeftClickedFunction(RenderWindow &window);
    void RightClickedFunction(RenderWindow &window);

    unsigned int GetCol();
    unsigned int GetRow();
};