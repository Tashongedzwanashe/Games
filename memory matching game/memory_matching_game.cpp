// Ahmad Tomeh 100001925
//Emmanuel Mufunde 100001936
//George Kilibwa 100002924
// Date: 18/06/2025
// Time: 12:40PM

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

// Function declarations
void initializeBoard(vector<vector<char>>& board, vector<vector<char>>& hiddenBoard, int size);
void displayBoard(const vector<vector<char>>& board, int size);
void shuffleBoard(vector<vector<char>>& board, int size);
bool makeMove(vector<vector<char>>& board, vector<vector<char>>& hiddenBoard, int size);
bool isGameComplete(const vector<vector<char>>& board, int size);
bool isValidMove(int row, int col, int size);

// Function to initialize the board with pairs
void initializeBoard(vector<vector<char>>& board, vector<vector<char>>& hiddenBoard, int size) {
    // Create pairs of letters (A-H for 4x4 board)
    char value = 'A';
    int pairs = (size * size) / 2;
    
    // Fill board with pairs
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = value;
            if ((i * size + j + 1) % 2 == 0) value++;
        }
    }
    
    // Shuffle the board
    shuffleBoard(board, size);
}

// Function to shuffle the board
void shuffleBoard(vector<vector<char>>& board, int size) {
    random_device rd;
    mt19937 gen(rd());
    
    for (int i = size - 1; i > 0; i--) {
        for (int j = size - 1; j > 0; j--) {
            uniform_int_distribution<> dis(0, i);
            uniform_int_distribution<> dis2(0, j);
            int randI = dis(gen);
            int randJ = dis2(gen);
            
            swap(board[i][j], board[randI][randJ]);
        }
    }
}

// Function to display the current state of the board
void displayBoard(const vector<vector<char>>& board, int size) {
    cout << "\n  ";
    for (int i = 0; i < size; i++) {
        cout << i << " ";
    }
    cout << "\n";
    
    for (int i = 0; i < size; i++) {
        cout << i << " ";
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Function to validate moves
bool isValidMove(int row, int col, int size) {
    return row >= 0 && row < size && col >= 0 && col < size;
}

// Function to handle a player's move
bool makeMove(vector<vector<char>>& board, vector<vector<char>>& hiddenBoard, int size) {
    int row1, col1, row2, col2;
    
    // First card
    do {
        cout << "Enter coordinates of first card (row col): ";
        cin >> row1 >> col1;
    } while (!isValidMove(row1, col1, size) || hiddenBoard[row1][col1] != '*');
    
    // Show first card
    hiddenBoard[row1][col1] = board[row1][col1];
    displayBoard(hiddenBoard, size);
    
    // Second card
    do {
        cout << "Enter coordinates of second card (row col): ";
        cin >> row2 >> col2;
    } while (!isValidMove(row2, col2, size) || hiddenBoard[row2][col2] != '*' || 
             (row1 == row2 && col1 == col2));
    
    // Show second card
    hiddenBoard[row2][col2] = board[row2][col2];
    displayBoard(hiddenBoard, size);
    
    // Check if cards match
    if (board[row1][col1] == board[row2][col2]) {
        cout << "Match found!\n";
        return true;
    } else {
        cout << "Not a match. Cards will be hidden.\n";
        this_thread::sleep_for(chrono::seconds(2));
        hiddenBoard[row1][col1] = '*';
        hiddenBoard[row2][col2] = '*';
        return true;
    }
}

// Function to check if the game is complete
bool isGameComplete(const vector<vector<char>>& board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '*') return false;
        }
    }
    return true;
}

// Main function
int main() {
    char playAgain;
    do {
        int size = 4; // Default board size (4x4)
        vector<vector<char>> board(size, vector<char>(size));
        vector<vector<char>> hiddenBoard(size, vector<char>(size, '*'));
        int moves = 0;
        
        cout << "Welcome to the Memory Matching Game!\n\n";
        
        initializeBoard(board, hiddenBoard, size);
        
        while (!isGameComplete(hiddenBoard, size)) {
            displayBoard(hiddenBoard, size);
            if (makeMove(board, hiddenBoard, size)) {
                moves++;
            }
            cout << "Moves so far: " << moves << endl;
        }
        
        cout << "\nCongratulations! You matched all pairs!\n";
        cout << "Total moves: " << moves << endl;
        
        cout << "Play again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
    
    cout << "Thank you for playing!\n";
    return 0;
}
