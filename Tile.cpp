#include "Tile.h"

// Constructor of this tile, everything is false, background, cover, and flag tileSprites are loaded
Tile::Tile(float x, float y, map<string, Texture> &textures) {
    // Default boolean values
    isDebugged = false;
    isMine = false;
    isFlagged = false;
    isRevealed = false;

    // Will be checking and update this value in DefineTile()
    nearByMineCount = 0;

    // Set background sprite's texture and position
    tileSprites["background"].setTexture(textures["tile_revealed"]);
    tileSprites["background"].setPosition(x, y);

    // Set cover sprite's texture and position
    tileSprites["cover"].setTexture(textures["tile_hidden"]);
    tileSprites["cover"].setPosition(x, y);

    // Set flag sprite's texture, position, and alpha value to 0
    tileSprites["flag"].setTexture(textures["flag"]);
    tileSprites["flag"].setPosition(x, y);
    tileSprites["flag"].setColor(Color(255, 255, 255, 0));

    // If the tile is a mine, icon will be mine, else will be number or tile_revealed.
    // Will be setting its texture in DefineTile()
    tileSprites["icon"].setPosition(x, y);
}

// Change the icon of the tile, mine, number, or nothing
void Tile::DefineTile(map<string, Texture> &textures) {
    ResetStats();
    nearByMineCount = 0;
    // Check the adjacent 8 tiles 1 by 1, if the tile is a mine, add 1 to the value above
    for (unsigned int i = 0; i < 8; i++) {
        if (adjacentTiles.at(i) != nullptr && adjacentTiles.at(i)->isMine) {
            nearByMineCount++;
        }
    }
    // If this tile is a mine, set the icon sprite to mine's image
    if (isMine) {
        tileSprites["icon"].setTexture(textures["mine"]);
    }
        // If is not mine
    else {
        // And then set the proper number as icon
        if (nearByMineCount == 0) {
            tileSprites["icon"].setTexture(textures["tile_revealed"]);
        }
        else if (nearByMineCount == 1) {
            tileSprites["icon"].setTexture(textures["number_1"]);
        }
        else if (nearByMineCount == 2) {
            tileSprites["icon"].setTexture(textures["number_2"]);
        }
        else if (nearByMineCount == 3) {
            tileSprites["icon"].setTexture(textures["number_3"]);
        }
        else if (nearByMineCount == 4) {
            tileSprites["icon"].setTexture(textures["number_4"]);
        }
        else if (nearByMineCount == 5) {
            tileSprites["icon"].setTexture(textures["number_5"]);
        }
        else if (nearByMineCount == 6) {
            tileSprites["icon"].setTexture(textures["number_6"]);
        }
        else if (nearByMineCount == 7) {
            tileSprites["icon"].setTexture(textures["number_7"]);
        }
        else if (nearByMineCount == 8) {
            tileSprites["icon"].setTexture(textures["number_8"]);
        }
    }
    // Hide the icon, flag, and only cover is visible
    tileSprites["icon"].setColor(Color(255, 255, 255, 0));
    tileSprites["flag"].setColor(Color(255, 255, 255, 0));
    tileSprites["cover"].setColor(Color(255, 255, 255, 255));
}

// Left click on tile to reveal it
void Tile::LeftClick(int &tileRevealed) {
    cout << "is Flagged: " << this->isFlagged << endl;
    cout << "is Mine: " << this->isMine << endl;
    cout << "is Revealed: " << this->isRevealed << endl;

    // If the tile is not already revealed
    if (!isRevealed) {
        // And if is not flagged, then u can click on it to reveal it
        if (!isFlagged) {
            isRevealed = true;
            tileRevealed++;
            // Hide cover sprite and show the hidden one with w/e the tile is
            tileSprites["cover"].setColor(Color(255, 255, 255, 0));
            tileSprites["icon"].setColor(Color(255, 255, 255, 255));

            // If there is no nearby Mines and tile itself is not a mine. reveal the adjacent Tiles
            if (nearByMineCount == 0 && !isMine) {
                for (unsigned int i = 0; i < 8; i++) {
                    if (adjacentTiles.at(i) != nullptr && !(adjacentTiles.at(i)->isMine)) {
                        adjacentTiles.at(i)->LeftClick(tileRevealed);
                    }
                }
            }
        }
        else {
            cout << "This is FLAGGED, not clickable!" << endl;
        }
    }
}

// Right click on tile to flag it
void Tile::RightClick() {
    cout << "is Flagged: " << this->isFlagged << endl;
    cout << "is Mine: " << this->isMine << endl;
    cout << "is Revealed: " << this->isRevealed << endl;

    // If the tile is not already revealed
    if (!isRevealed) {
        // If is already flagged, undo it and hide the flag
        if (isFlagged) {
            isFlagged = false;
            tileSprites["flag"].setColor(Color(255, 255, 255, 0));
        }
        // Else flag the tile and show the flag icon
        else{
            isFlagged = true;
            tileSprites["flag"].setColor(Color(255, 255, 255, 255));
        }
    }
}

// Click on the debug button to show all mines
void Tile::Debug() {
    // If the tile is not already revealed
    if (!isRevealed) {
        // And if the tile is a mine
        if (isMine) {
            // If the debug mode is already activated, turn in off
            if (isDebugged) {
                isDebugged = false;
                tileSprites["icon"].setColor(Color(255, 255, 255, 0));
            }
            // Else turn on the debugged mode and show the mine
            else {
                isDebugged = true;
                tileSprites["icon"].setColor(Color(255, 255, 255, 255));
            }
        }
    }
}

// Draw the tile, (1)background tile (2)the corresponding icon (3)cover (4)flag
void Tile::DrawTile(RenderWindow &window) {
    window.draw(tileSprites["background"]);
    window.draw(tileSprites["cover"]);
    window.draw(tileSprites["icon"]);
    window.draw(tileSprites["flag"]);
}

// Depending on the random generation, set this tile to mine or not
void Tile::SetMine(bool isMine) {
    this->isMine = isMine;
}

void Tile::ResetStats() {
    this->isRevealed = false;
    this->isFlagged = false;
    this->isDebugged = false;
}

/*********** Getters ***********/
bool Tile::GetIsDebugged() const {
    return this->isDebugged;
}

bool Tile::GetIsMine() const {
    return this->isMine;
}

bool Tile::GetIsFlagged() const {
    return this->isFlagged;
}

bool Tile::GetIsRevealed() const {
    return this->isRevealed;
}

unsigned int Tile::GetNearByMineCount() const {
    return this->nearByMineCount;
}

map<String, Sprite> Tile::GetSprites() {
    return this->tileSprites;
}