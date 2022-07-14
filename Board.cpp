#include "Board.h"

// Board Constructor
Board::Board() {
    // Get randomized seeds base on time
    srand(time(0));
    // Read the config.cfg file to get the numOfCols, numOfRows, mineCount
    ReadConfigFile();
    // set tileCount
    this->tileCount = this->numOfCols * this->numOfRows;
    this->tileShowed = 0;
    this->tileLeft = this->tileCount;
    this->digitsMineCount = (int)(this->mineCount);

    this->gameOver = false;
    this->lost= false;
    // Load the test cases
    LoadTests();
    // Load all the textures into textures map storage system
    LoadTextures();
    // Create the tiles for the game base on numOfCols, numOfRows, tileCount
    CreateTiles();
    AssignRandomMines();
}

// Get the values from config.cfg
void Board::ReadConfigFile() {
    ifstream file("boards/config.cfg");
    if (file.is_open()) {
        while (getline(file, noc)) {
            this->numOfCols = stoi(noc);
            getline(file, nor);
            this->numOfRows = stoi(nor);
            getline(file, mc);
            this->mineCount = stoi(mc);
        }
    }
}

// Set the mines for the whole board
void Board::SetMines()  {
    // Set the mines for the board 1 by 1 for each tile
    for (unsigned int i = 0; i < tileCount; i++) {
        tiles.at(i).SetMine(isMines.at(i));
    }
}

// Click the debug icon, call Tile::Debug()
void Board::Debug() {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        tiles.at(i).Debug();
    }
}

// Draw the board to game window
void Board::DrawBoard(RenderWindow &window) {
    // Drawing a board means drawing all the tiles with the digit at bottom left, face at bottom, and other functionalities at bottom right
    for (unsigned int i = 0; i < tileCount; i++) {
        // Drawing the tiles
        tiles.at(i).DrawTile(window);
    }
    // Drawing the digit
    window.draw(boardSprite["digits"]);
    // Drawing the face
    // Update accordingly via UpdateFace()
    window.draw(boardSprite["face"]);
    // Drawing the debugger
    window.draw(boardSprite["debug"]);
    // Drawing the tests
    window.draw(boardSprite["test_1"]);
    window.draw(boardSprite["test_2"]);
    window.draw(boardSprite["test_3"]);
    // Drawing the digits
    window.draw(digitSprite[-1]);
    window.draw(digitSprite[1]);
    window.draw(digitSprite[2]);
    window.draw(digitSprite[3]);
}

// Create all the tiles for the game row by row, col by col
void Board::CreateTiles() {
    // Each tile image is 32x32
    float x = 32.0f;
    float y = 32.0f;

    for (unsigned int j = 0; j < numOfRows; j++) {
        for (unsigned int i = 0; i < numOfCols; i++) {
            // Add a new tile to the vector and then move to the next position
            Tile newTile = Tile(x * (float)i, y * (float)j, textures);
            tiles.push_back(newTile);
        }
    }
}

// Load all the textures from images folder
void Board::LoadTextures() {
    Texture newTexture;
    // Debug Button
    newTexture.loadFromFile("images/debug.png");
    textures["debug"] = newTexture;
    // Digits
    newTexture.loadFromFile("images/digits.png");
    textures["digits"] = newTexture;
    // Faces
    newTexture.loadFromFile("images/face_happy.png");
    textures["face_happy"] = newTexture;
    newTexture.loadFromFile("images/face_lose.png");
    textures["face_lose"] = newTexture;
    newTexture.loadFromFile("images/face_win.png");
    textures["face_win"] = newTexture;
    // Flag
    newTexture.loadFromFile("images/flag.png");
    textures["flag"] = newTexture;
    // Mine
    newTexture.loadFromFile("images/mine.png");
    textures["mine"] = newTexture;
    // Numbers
    newTexture.loadFromFile("images/number_1.png");
    textures["number_1"] = newTexture;
    newTexture.loadFromFile("images/number_2.png");
    textures["number_2"] = newTexture;
    newTexture.loadFromFile("images/number_3.png");
    textures["number_3"] = newTexture;
    newTexture.loadFromFile("images/number_4.png");
    textures["number_4"] = newTexture;
    newTexture.loadFromFile("images/number_5.png");
    textures["number_5"] = newTexture;
    newTexture.loadFromFile("images/number_6.png");
    textures["number_6"] = newTexture;
    newTexture.loadFromFile("images/number_7.png");
    textures["number_7"] = newTexture;
    newTexture.loadFromFile("images/number_8.png");
    textures["number_8"] = newTexture;
    // Tests
    newTexture.loadFromFile("images/test_1.png");
    textures["test_1"] = newTexture;
    newTexture.loadFromFile("images/test_2.png");
    textures["test_2"] = newTexture;
    newTexture.loadFromFile("images/test_3.png");
    textures["test_3"] = newTexture;
    // Tile
    newTexture.loadFromFile("images/tile_hidden.png");
    textures["tile_hidden"] = newTexture;
    newTexture.loadFromFile("images/tile_revealed.png");
    textures["tile_revealed"] = newTexture;

    // Set the position of some sprites here at board's initiation, because these sprite wont move or change during gameplay
    // Digits
    digitSprite[-1].setTexture(textures["digits"]);
    digitSprite[-1].setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
    digitSprite[-1].setPosition(0, (float)numOfRows * 32);
    digitSprite[-1].setColor(Color(255,255,255,0));
    digitSprite[3].setTexture(textures["digits"]);
    digitSprite[3].setTextureRect(Rect<int>(21 * 0, 0, 21, 32));
    digitSprite[3].setPosition(21, (float)numOfRows * 32);
    digitSprite[2].setTexture(textures["digits"]);
    digitSprite[2].setTextureRect(Rect<int>(21 * 0, 0, 21, 32));
    digitSprite[2].setPosition(42, (float)numOfRows * 32);
    digitSprite[1].setTexture(textures["digits"]);
    digitSprite[1].setTextureRect(Rect<int>(21 * 0, 0, 21, 32));
    digitSprite[1].setPosition(63, (float)numOfRows * 32);
    // Face
    boardSprite["face"].setTexture(textures["face_happy"]);
    boardSprite["face"].setPosition((((float)numOfCols * 32) / 2) - 32, (float)numOfRows * 32);
    // Debug
    boardSprite["debug"].setTexture(textures["debug"]);
    boardSprite["debug"].setPosition((((float)numOfCols * 32) / 2) + 96,(float)numOfRows * 32);
    // Tests
    boardSprite["test_1"].setTexture(textures["test_1"]);
    boardSprite["test_1"].setPosition((((float)numOfCols * 32) / 2) + 160, (float)numOfRows * 32);
    boardSprite["test_2"].setTexture(textures["test_2"]);
    boardSprite["test_2"].setPosition((((float)numOfCols * 32) / 2) + 224, (float)numOfRows * 32);
    boardSprite["test_3"].setTexture(textures["test_3"]);
    boardSprite["test_3"].setPosition((((float)numOfCols * 32) / 2) + 288, (float)numOfRows * 32);
}

// Update Face base on the win, loss, or gaming condition
void Board::UpdateFace() {
    // Check if the game is over
    if (gameOver) {
        // If the game is over and player won, face is win face
        if (lost) {
            boardSprite["face"].setTexture(textures["face_lose"]);
        }
        // Else the face is lose face
        else {
            boardSprite["face"].setTexture(textures["face_win"]);
        }
    }
    // If the game is still playing, face is happy face
    else {
        boardSprite["face"].setTexture(textures["face_happy"]);
    }
}

// Create a int vector which stores mineCount amount of
// random number from range 0 to tileCount
// then use that vector to assign true or false value to isMines
// vector via the corresponding number as index
// MORE LIKE A RESET
void Board::AssignRandomMines() {
    // Reset the isMines vector, since there is a chance the previous gaming section data is left over
    isMines.clear();

    this->mineCount = stoi(this->mc);

    vector<int> mines;
    int randomNumber;
    bool uniqueNumber = false;

    int DebuggingMineCount = 0;

    // Need mineCount of random numbers
    for (unsigned int i = 0; i < mineCount; i++) {
        // While the random number that is generated is not unique, keep finding a new random number
        while (!uniqueNumber) {
            randomNumber = rand() % tileCount;
            if (find(mines.begin(), mines.end(), randomNumber) == mines.end()) {
                    uniqueNumber = true;
                    mines.push_back(randomNumber);
                }
            }
        uniqueNumber = false;
        }

    // After getting mineCount amount of random numbers, time to store them in isMines vector as ture or false values
    for (int i = 0; i < tileCount; i++) {
        // If we find tiles.at(i) starting from 0 in mines. push it to true
        if (find(mines.begin(), mines.end(), i) != mines.end()) {
            isMines.push_back(true);
            DebuggingMineCount++;
        }
        // Else push it false
        else {
            isMines.push_back(false);
        }
    }
    // After the mines are randomly generated, set them up
    SetMines();
    SetSpritesToTiles();

    // Reset other stuff
    digitsMineCount = (int)mineCount;
    UpdateDigits();
    gameOver = false;
    lost = false;
    tileShowed = 0;
    tileLeft = this->tileCount;
}

// Update the game after each mouse click, whether that is left click or right click
void Board::LeftClickedFunction(RenderWindow &window) {
    // Mouse Position
    Vector2i mousePosition = Mouse::getPosition(window);
    cout << "Position of mouse: " << "x = " << mousePosition.x << ", y = " << mousePosition.y << endl;
    // If the mouse is clicked inside the tile boundary (only clickable during game)
    if (mousePosition.y >= 0 && mousePosition.y < numOfRows * 32 && !gameOver) {
        if (mousePosition.x >= 0 && mousePosition.x < (numOfCols * 32)) {
            // Works like a floor function, 5 / 2 = 2
            int tileX = mousePosition.x / 32;
            int tileY = mousePosition.y / 32;
            int tileNumber = (int)(tileX + tileY * numOfCols);

            int clicked = 0;
            // After finding which tile the mouse were being clicked,
            // Execute the LeftClick()
            tiles.at(tileNumber).LeftClick(clicked);
            // If is mine, game over, you lose, and reveal all the mines
            if (!tiles.at(tileNumber).GetIsFlagged() && tiles.at(tileNumber).GetIsMine()) {
                gameOver = true;
                lost = true;
                int trashClicked = 0;
                for (unsigned int i = 0; i < tileCount; i++) {
                    if (tiles.at(i).GetIsMine()) {
                        if (tiles.at(i).GetIsFlagged()) {
                            tiles.at(i).isFlagged = false;
                        }
                        if (i != tileNumber) {
                            tiles.at(i).LeftClick(trashClicked);
                        }
                    }
                }
            }
            else {
                tileShowed = tileShowed + clicked;
                tileLeft = tileLeft - clicked;
            }
        }
    }
        // If the mouse if clicked outside the tile boundary, meaning the bottom menu area
    else if (mousePosition.y >= numOfRows * 32 && mousePosition.y < numOfRows * 32 + 88) {
        // If is the face, meaning reset the game
        if (mousePosition.x >= (numOfCols * 32 / 2) - 32 && mousePosition.x < (numOfCols * 32 / 2) + 32) {
            // Reset the game
            AssignRandomMines();
        }
            // If is the Debug button
        else if (mousePosition.x >= (numOfCols * 32 / 2) + 96 && mousePosition.x < (numOfCols * 32 / 2) + 160) {
            if (!gameOver) {
                Debug();
            }
        }
            // If is the test buttons
            // Test 1
        else if (mousePosition.x >= (numOfCols * 32 / 2) + 160 && mousePosition.x < (numOfCols * 32 / 2) + 224) {
            LoadTest1();
        }
        else if (mousePosition.x >= (numOfCols * 32 / 2) + 224 && mousePosition.x < (numOfCols * 32 / 2) + 288) {
            LoadTest2();
        }
        else if (mousePosition.x >= (numOfCols * 32 / 2) + 288 && mousePosition.x < (numOfCols * 32 / 2) + 352) {
            LoadTest3();
        }
    }
}

void Board::RightClickedFunction(RenderWindow &window) {
    // Mouse Position
    Vector2i mousePosition = Mouse::getPosition(window);
    // If the mouse is clicked inside the tile boundary (only clickable during game)
    if (mousePosition.x >= 0 && mousePosition.x < numOfCols * 32 && !gameOver) {
        if (mousePosition.y >= 0 && mousePosition.y < numOfRows * 32) {
            // Works like a floor function, 5 / 2 = 2
            int tileX = mousePosition.x / 32;
            int tileY = mousePosition.y / 32;
            int tileNumber = (int)(tileX + tileY * numOfCols);
            // If the tile is already flagged, take remove the flag and add back 1 digit
            if (tiles.at(tileNumber).GetIsFlagged() && !tiles.at(tileNumber).GetIsRevealed()) {
                tiles.at(tileNumber).RightClick();
                digitsMineCount++;
            }
                // Else put on a flag and remove 1 digit
            else {
                tiles.at(tileNumber).RightClick();
                digitsMineCount--;
            }
            UpdateDigits();
        }
    }
}

void Board::UpdateGame(RenderWindow &window) {
    // While we updating the game, if the left tiles are all mines, which means player beat the game
    if ((tileLeft == mineCount) && !gameOver && !lost) {
        // mark all the left tiles, aka the mines flag
        gameOver = true;
        lost = false;
        digitsMineCount = 0;
        for (auto & tile : tiles) {
            if (tile.GetIsMine() && !tile.GetIsFlagged()) {
                tile.RightClick();
            }
            if (tile.GetIsMine() && tile.GetIsDebugged()) {
                // If is in debug mode, upon wining the game, switch debug mode off.
                tile.Debug();
            }
        }
    }

    UpdateFace();
    UpdateDigits();
    DrawBoard(window);
}

void Board::SetSpritesToTiles() {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        // Reset the adjacent tiles
        tiles.at(i).adjacentTiles.clear();
        // Set all the adjacent tiles to null by default, and change them accordingly
        for (unsigned int j = 0; j < 8; j++) {
            tiles.at(i).adjacentTiles.push_back(nullptr);

        }
        // If this tile is the 1st tile (TOP LEFT), which has only 3 adjacent tiles.
        if (i == 0) {
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
            tiles.at(i).adjacentTiles.at(7) = &(tiles.at(i + numOfCols + 1));
        }
        // Else if this tile is on the top of the grid, which has 5 adjacent tiles.
        else if (i > 0 && i < numOfCols - 1) {
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
            tiles.at(i).adjacentTiles.at(5) = &(tiles.at(i + numOfCols - 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
            tiles.at(i).adjacentTiles.at(7) = &(tiles.at(i + numOfCols + 1));
        }
        // Else if this tile is on the TOP RIGHT, which has only 3 adjacent tiles.
        else if (i == (numOfCols - 1)) {
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
            tiles.at(i).adjacentTiles.at(5) = &(tiles.at(i + numOfCols - 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
        }
        // Else if this tile is on the left wall, which has 5 adjacent tiles.
        else if (i != (numOfCols * (numOfRows - 1)) && (i % numOfCols == 0)) {
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(2) = &(tiles.at(i - numOfCols + 1));
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
            tiles.at(i).adjacentTiles.at(7) = &(tiles.at(i + numOfCols + 1));
        }
        // Else if this tile is on the BOTTOM LEFT. which has only 3 adjacent tiles.
        else if (i == numOfCols * (numOfRows - 1)) {
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(2) = &(tiles.at(i - numOfCols + 1));
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
        }
        // Else if this tile is on the right wall, which has 5 adjacent tiles.
        else if (i != (numOfCols - 1) && i != (numOfCols * numOfRows - 1) && ((i - (numOfCols - 1)) % numOfCols == 0)) {
            tiles.at(i).adjacentTiles.at(0) = &(tiles.at(i - numOfCols - 1));
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
            tiles.at(i).adjacentTiles.at(5) = &(tiles.at(i + numOfCols - 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
        }
        // Else if this tile is on the BOTTOM RIGHT, which has only 3 adjacent tiles.
        else if (i == numOfCols * numOfRows - 1) {
            tiles.at(i).adjacentTiles.at(0) = &(tiles.at(i - numOfCols - 1));
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
        }
        // Else if this tile is on the bottom wall, which has 5 adjacent tiles.
        else if (i > (numOfCols * (numOfRows - 1)) && i < (numOfCols * numOfRows - 1)) {
            tiles.at(i).adjacentTiles.at(0) = &(tiles.at(i - numOfCols - 1));
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(2) = &(tiles.at(i - numOfCols + 1));
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
        }
        // Else if this tile is in the middle, which has 8 adjacent tiles.
        else {
            tiles.at(i).adjacentTiles.at(0) = &(tiles.at(i - numOfCols - 1));
            tiles.at(i).adjacentTiles.at(1) = &(tiles.at(i - numOfCols));
            tiles.at(i).adjacentTiles.at(2) = &(tiles.at(i - numOfCols + 1));
            tiles.at(i).adjacentTiles.at(3) = &(tiles.at(i - 1));
            tiles.at(i).adjacentTiles.at(4) = &(tiles.at(i + 1));
            tiles.at(i).adjacentTiles.at(5) = &(tiles.at(i + numOfCols - 1));
            tiles.at(i).adjacentTiles.at(6) = &(tiles.at(i + numOfCols));
            tiles.at(i).adjacentTiles.at(7) = &(tiles.at(i + numOfCols + 1));
        }
        tiles.at(i).DefineTile(textures);
    }
}

void Board::LoadTests() {
    ifstream file("boards/testboard1.brd");
    string newLine;
    if (file.is_open()) {
        // Read each line and store is boolean value to vector test1Mines.
        while (getline(file, newLine)) {
            for (unsigned int i = 0; i < newLine.length(); i++) {
                if (newLine.at(i) == '1') {
                    test1Mines.push_back(true);
                }
                else {
                    test1Mines.push_back(false);
                }
            }
        }
    }
    file.close();

    file.open("boards/testboard2.brd");
    if (file.is_open()) {
        // Read each line and store is boolean value to vector test1Mines.
        while (getline(file, newLine)) {
            for (unsigned int i = 0; i < newLine.size(); i++) {
                if (newLine.at(i) == '1') {
                    test2Mines.push_back(true);
                }
                else {
                    test2Mines.push_back(false);
                }
            }
        }
    }
    file.close();

    file.open("boards/testboard3.brd");
    if (file.is_open()) {
        // Read each line and store is boolean value to vector test1Mines.
        while (getline(file, newLine)) {
            for (unsigned int i = 0; i < newLine.size(); i++) {
                if (newLine.at(i) == '1') {
                    test3Mines.push_back(true);
                }
                else {
                    test3Mines.push_back(false);
                }
            }
        }
    }
    file.close();
}

void Board::LoadTest1() {
    // Clear the existing mines
    isMines.clear();

    mineCount = 0;

    // Set the mines for the board 1 by 1 for each tile
    for (unsigned int i = 0; i < tileCount; i++) {
        if (test1Mines.at(i) == 1) {
            mineCount++;
        }
        tiles.at(i).SetMine(test1Mines.at(i));
    }
    SetSpritesToTiles();
    // Reset other stuff
    digitsMineCount = (int)mineCount;
    UpdateDigits();
    gameOver = false;
    lost = false;
    tileShowed = 0;
    tileLeft = this->tileCount;
}

void Board::LoadTest2() {
    // Clear the existing mines
    isMines.clear();
    mineCount = 0;

    // Set the mines for the board 1 by 1 for each tile
    for (unsigned int i = 0; i < tileCount; i++) {
        if (test2Mines.at(i) == 1) {
            mineCount++;
        }
        tiles.at(i).SetMine(test2Mines.at(i));
    }
    SetSpritesToTiles();
    // Reset other stuff
    digitsMineCount = (int)mineCount;
    UpdateDigits();
    gameOver = false;
    lost = false;
    tileShowed = 0;
    tileLeft = this->tileCount;
}

void Board::LoadTest3() {
    // Clear the existing mines
    isMines.clear();
    mineCount = 0;

    // Set the mines for the board 1 by 1 for each tile
    for (unsigned int i = 0; i < tileCount; i++) {
        if (test3Mines.at(i) == 1) {
            mineCount++;
        }
        tiles.at(i).SetMine(test3Mines.at(i));
    }
    SetSpritesToTiles();
    // Reset other stuff
    digitsMineCount = (int)mineCount;
    UpdateDigits();
    gameOver = false;
    lost = false;
    tileShowed = 0;
    tileLeft = this->tileCount;
}

unsigned int Board::GetCol() {
    return numOfCols;
}

unsigned int Board::GetRow() {
    return numOfRows;
}

void Board::UpdateDigits() {
    int temp = digitsMineCount;
    int firstDigit = 0;
    int secondDigit = 0;
    int thirdDigit = 0;

    if (temp >= 0) {
        digitSprite[-1].setColor(Color(255,255,255,0));
        if (temp >= 100) {
            firstDigit = temp % 10;
            secondDigit = (temp / 10) % 10;
            thirdDigit = (temp / 100) % 10;
        } else {
            firstDigit = temp % 10;
            secondDigit = (temp / 10) % 10;
            thirdDigit = 0;
        }
    }
    else if (temp < 0) {
        digitSprite[-1].setColor(Color(255,255,255,255));
        if (-temp >= 100) {
            firstDigit = -temp % 10;
            secondDigit = (-temp / 10) % 10;
            thirdDigit = (-temp / 100) % 10;
        }
        else if (0 < -temp && -temp < 100) {
            firstDigit = -temp % 10;
            secondDigit = (-temp / 10) % 10;
            thirdDigit = 0;
        }
    }

    digitSprite[3].setTextureRect(Rect<int>(21 * thirdDigit, 0, 21, 32));
    digitSprite[2].setTextureRect(Rect<int>(21 * secondDigit, 0, 21, 32));
    digitSprite[1].setTextureRect(Rect<int>(21 * firstDigit, 0, 21, 32));
}