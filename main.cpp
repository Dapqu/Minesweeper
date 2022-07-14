#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Board.h"

using namespace std;
using namespace sf;

int main() {
    Board board;

    RenderWindow window(VideoMode(board.GetCol() *  32,board.GetRow() * 32 + 88), "Minesweeper");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            // The reason why I use MouseButtonReleased is so that user won't spam click and accidentally lose the game
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                board.LeftClickedFunction(window);
            }
            // Same reason as above
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
                board.RightClickedFunction(window);
            }

            window.clear(Color::White);
            board.UpdateGame(window);
            window.display();
        }
    }
    return 0;
}
