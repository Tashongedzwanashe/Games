// Minesweeper game
// Author: Mufunde Emmanuel-100001936, George Kilibwa - 100002624, Riad Al Zaim- 100003048
// Date: 2025-06-25 (1230 hrs)
// Description: A simple Minesweeper game implemented in C++.

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

// Clears the console screen.
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI escape code for clearing screen
    std::cout << "\033[2J\033[1;1H";
#endif
}

// Represents a single cell on the Minesweeper board.
struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int adjacentMines = 0;
};

// Represents the Minesweeper game board and manages game logic.
class Board {
public:
    // Constructor to initialize the board with a given size and number of mines.
    Board(int width, int height, int mines)
        : width(width), height(height), mineCount(mines), remainingCells(width * height - mines), firstMove(true) {
        grid.resize(height, std::vector<Cell>(width));
    }

    // Runs the main game loop.
    void run() {
        while (!isGameOver()) {
            printBoard();
            promptInput();
        }
        revealAll();
        printBoard();
        if (checkWin()) {
            std::cout << "Congratulations! You have cleared all the mines!" << std::endl;
        } else {
            std::cout << "Game Over! You hit a mine." << std::endl;
        }
    }

private:
    int width;
    int height;
    int mineCount;
    int remainingCells;
    bool firstMove;
    std::vector<std::vector<Cell>> grid;

    // Places mines randomly on the board, avoiding the first clicked cell.
    void placeMines(int startX, int startY) {
        srand(time(0));
        for (int i = 0; i < mineCount; ++i) {
            int x, y;
            do {
                x = rand() % width;
                y = rand() % height;
            } while (grid[y][x].isMine || (x == startX && y == startY));
            grid[y][x].isMine = true;
        }

        // Calculate adjacent mines for all cells.
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (!grid[y][x].isMine) {
                    grid[y][x].adjacentMines = countAdjacentMines(x, y);
                }
            }
        }
    }

    // Counts the number of mines adjacent to a given cell.
    int countAdjacentMines(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (isValid(nx, ny) && grid[ny][nx].isMine) {
                    count++;
                }
            }
        }
        return count;
    }

    // Reveals a cell and handles the game logic for the reveal.
    void revealCell(int x, int y) {
        if (!isValid(x, y) || grid[y][x].isRevealed || grid[y][x].isFlagged) {
            return;
        }

        if (firstMove) {
            placeMines(x, y);
            firstMove = false;
        }

        grid[y][x].isRevealed = true;

        if (grid[y][x].isMine) {
            return; // Game over, will be handled in the main loop
        }

        remainingCells--;

        if (grid[y][x].adjacentMines == 0) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    revealCell(x + dx, y + dy);
                }
            }
        }
    }

    // Toggles a flag on a cell.
    void toggleFlag(int x, int y) {
        if (isValid(x, y) && !grid[y][x].isRevealed) {
            grid[y][x].isFlagged = !grid[y][x].isFlagged;
        }
    }

    // Prints the current state of the board to the console.
    void printBoard() {
        clearScreen();
        std::cout << "   ";
        for (int x = 0; x < width; ++x) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        std::cout << "  ";
        for (int x = 0; x < width; ++x) {
            std::cout << "--";
        }
        std::cout << std::endl;


        for (int y = 0; y < height; ++y) {
            std::cout << y << " |";
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].isRevealed) {
                    if (grid[y][x].isMine) {
                        std::cout << "* ";
                    } else if (grid[y][x].adjacentMines > 0) {
                        std::cout << grid[y][x].adjacentMines << " ";
                    } else {
                        std::cout << ". ";
                    }
                } else if (grid[y][x].isFlagged) {
                    std::cout << "F ";
                } else {
                    std::cout << "# ";
                }
            }
            std::cout << std::endl;
        }
    }

    // Prompts the user for their move and processes it.
    void promptInput() {
        std::cout << "\nEnter command (r_y_x to reveal, f_y_x to flag): ";
        std::string input;
        std::cin >> input;

        std::stringstream ss(input);
        char command;
        int r, c;
        char underscore;

        ss >> command >> underscore >> r >> underscore >> c;

        if (command == 'r') {
            revealCell(c, r);
        } else if (command == 'f') {
            toggleFlag(c, r);
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
            // Add a small delay so the user can see the message
            #ifdef _WIN32
                system("timeout /t 1 /nobreak >nul");
            #else
                system("sleep 1");
            #endif
        }
    }

    // Checks if the game is over (win or loss).
    bool isGameOver() {
        if (checkWin()) {
            return true;
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].isMine && grid[y][x].isRevealed) {
                    return true; // A mine was revealed
                }
            }
        }
        return false;
    }

    // Checks if the player has won the game.
    bool checkWin() {
        return remainingCells == 0;
    }

    // Checks if the given coordinates are within the board boundaries.
    bool isValid(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    // Reveals all cells at the end of the game.
    void revealAll() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                grid[y][x].isRevealed = true;
            }
        }
    }
};

int main() {
    int width, height, mines;

    std::cout << "Enter board width: ";
    std::cin >> width;
    std::cout << "Enter board height: ";
    std::cin >> height;
    std::cout << "Enter number of mines: ";
    std::cin >> mines;

    if (mines >= width * height) {
        std::cout << "Number of mines must be less than the total number of cells." << std::endl;
        return 1;
    }

    Board game(width, height, mines);
    game.run();

    return 0;
} 