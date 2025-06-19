// Conway's Game of Life Implementation
// Authors: [Your Names]
// Date: [Current Date]
// Description: A cellular automaton simulation with multiple game modes and win conditions

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Game configuration constants
const int DEFAULT_ROWS = 20;
const int DEFAULT_COLS = 40;
const int MAX_GENERATIONS = 1000;
const int DISPLAY_DELAY_MS = 500;

// Game states
enum class GameMode {
    STABILITY_GOAL,
    SURVIVAL_GOAL,
    PATTERN_CREATION,
    POPULATION_TARGET,
    TIME_ATTACK
};

// Function declarations
void initializeGrid(vector<vector<bool>>& grid, int rows, int cols);
void displayGrid(const vector<vector<bool>>& grid, int generation, int liveCells);
void randomFill(vector<vector<bool>>& grid, double density = 0.3);
void manualSetup(vector<vector<bool>>& grid);
int countLiveNeighbors(const vector<vector<bool>>& grid, int row, int col, int rows, int cols);
void evolveGrid(vector<vector<bool>>& grid, vector<vector<bool>>& nextGrid, int rows, int cols);
void saveGrid(const vector<vector<bool>>& grid, const string& filename);
bool loadGrid(vector<vector<bool>>& grid, const string& filename);
int countLiveCells(const vector<vector<bool>>& grid);
bool isStable(const vector<vector<bool>>& current, const vector<vector<bool>>& previous);
bool checkPattern(const vector<vector<bool>>& grid, const vector<vector<bool>>& pattern);
void runSimulation(vector<vector<bool>>& grid, int rows, int cols, GameMode mode, int targetGenerations);
void showMenu();
void showGameModes();

int main() {
    cout << "=== Conway's Game of Life ===\n\n";
    
    int rows, cols;
    cout << "Enter grid dimensions (rows columns): ";
    cin >> rows >> cols;
    
    if (rows <= 0 || cols <= 0 || rows > 100 || cols > 100) {
        cout << "Invalid dimensions. Using default 20x40.\n";
        rows = DEFAULT_ROWS;
        cols = DEFAULT_COLS;
    }
    
    vector<vector<bool>> grid(rows, vector<bool>(cols, false));
    vector<vector<bool>> nextGrid(rows, vector<bool>(cols, false));
    
    // Initialize grid
    initializeGrid(grid, rows, cols);
    
    char choice;
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                randomFill(grid);
                break;
            case '2':
                manualSetup(grid);
                break;
            case '3':
                showGameModes();
                int gameModeChoice;
                cin >> gameModeChoice;
                
                GameMode mode;
                int targetGenerations;
                
                switch (gameModeChoice) {
                    case 1:
                        mode = GameMode::STABILITY_GOAL;
                        cout << "Enter target generations for stability: ";
                        cin >> targetGenerations;
                        break;
                    case 2:
                        mode = GameMode::SURVIVAL_GOAL;
                        cout << "Enter generations to survive: ";
                        cin >> targetGenerations;
                        break;
                    case 3:
                        mode = GameMode::PATTERN_CREATION;
                        targetGenerations = 50;
                        cout << "Pattern creation mode - create a glider pattern!\n";
                        break;
                    case 4:
                        mode = GameMode::POPULATION_TARGET;
                        cout << "Enter target population range (min max): ";
                        int minPop, maxPop;
                        cin >> minPop >> maxPop;
                        targetGenerations = 100;
                        break;
                    case 5:
                        mode = GameMode::TIME_ATTACK;
                        targetGenerations = MAX_GENERATIONS;
                        cout << "Time attack mode - survive as long as possible!\n";
                        break;
                    default:
                        cout << "Invalid choice. Using survival mode.\n";
                        mode = GameMode::SURVIVAL_GOAL;
                        targetGenerations = 50;
                }
                
                runSimulation(grid, rows, cols, mode, targetGenerations);
                break;
            case '4':
                {
                    string filename;
                    cout << "Enter filename to save: ";
                    cin >> filename;
                    saveGrid(grid, filename);
                }
                break;
            case '5':
                {
                    string filename;
                    cout << "Enter filename to load: ";
                    cin >> filename;
                    if (loadGrid(grid, filename)) {
                        cout << "Grid loaded successfully!\n";
                    } else {
                        cout << "Failed to load grid.\n";
                    }
                }
                break;
            case '6':
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        if (choice != '6') {
            displayGrid(grid, 0, countLiveCells(grid));
        }
        
    } while (choice != '6');
    
    return 0;
}

void initializeGrid(vector<vector<bool>>& grid, int rows, int cols) {
    // Grid is already initialized with false values
    cout << "Grid initialized with " << rows << "x" << cols << " dimensions.\n";
}

void displayGrid(const vector<vector<bool>>& grid, int generation, int liveCells) {
    system("cls"); // Clear screen (Windows)
    
    cout << "=== Conway's Game of Life ===\n";
    cout << "Generation: " << generation << " | Live Cells: " << liveCells << "\n\n";
    
    // Print column numbers
    cout << "   ";
    for (int j = 0; j < grid[0].size(); j++) {
        cout << (j % 10) << " ";
    }
    cout << "\n";
    
    for (int i = 0; i < grid.size(); i++) {
        cout << (i < 10 ? " " : "") << i << " ";
        for (int j = 0; j < grid[i].size(); j++) {
            cout << (grid[i][j] ? "■ " : ". ");
        }
        cout << "\n";
    }
    cout << "\n";
}

void randomFill(vector<vector<bool>>& grid, double density) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] = dis(gen) < density;
        }
    }
    
    cout << "Grid filled randomly with density " << (density * 100) << "%\n";
}

void manualSetup(vector<vector<bool>>& grid) {
    cout << "Manual setup mode. Enter coordinates (row col) for live cells.\n";
    cout << "Enter -1 -1 to finish.\n";
    
    // Clear grid first
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] = false;
        }
    }
    
    int row, col;
    int count = 0;
    
    while (true) {
        cout << "Enter coordinates (row col): ";
        cin >> row >> col;
        
        if (row == -1 && col == -1) break;
        
        if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size()) {
            grid[row][col] = true;
            count++;
            cout << "Cell (" << row << "," << col << ") set to alive. Total: " << count << "\n";
        } else {
            cout << "Invalid coordinates. Please try again.\n";
        }
    }
    
    cout << "Manual setup complete. " << count << " cells set to alive.\n";
}

int countLiveNeighbors(const vector<vector<bool>>& grid, int row, int col, int rows, int cols) {
    int count = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            
            int neighborRow = (row + i + rows) % rows; // Periodic boundary conditions
            int neighborCol = (col + j + cols) % cols;
            
            if (grid[neighborRow][neighborCol]) {
                count++;
            }
        }
    }
    
    return count;
}

void evolveGrid(vector<vector<bool>>& grid, vector<vector<bool>>& nextGrid, int rows, int cols) {
    // Synchronous update - all cells updated simultaneously
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countLiveNeighbors(grid, i, j, rows, cols);
            
            if (grid[i][j]) {
                // Live cell
                nextGrid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                // Dead cell
                nextGrid[i][j] = (neighbors == 3);
            }
        }
    }
    
    // Copy next generation to current grid
    grid = nextGrid;
}

void saveGrid(const vector<vector<bool>>& grid, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    
    file << grid.size() << " " << grid[0].size() << "\n";
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            file << (grid[i][j] ? "1" : "0") << " ";
        }
        file << "\n";
    }
    
    file.close();
    cout << "Grid saved to " << filename << "\n";
}

bool loadGrid(vector<vector<bool>>& grid, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file for reading.\n";
        return false;
    }
    
    int rows, cols;
    file >> rows >> cols;
    
    if (rows != grid.size() || cols != grid[0].size()) {
        cout << "Error: Grid dimensions don't match.\n";
        return false;
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value;
            file >> value;
            grid[i][j] = (value == 1);
        }
    }
    
    file.close();
    return true;
}

int countLiveCells(const vector<vector<bool>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j]) count++;
        }
    }
    return count;
}

bool isStable(const vector<vector<bool>>& current, const vector<vector<bool>>& previous) {
    for (int i = 0; i < current.size(); i++) {
        for (int j = 0; j < current[i].size(); j++) {
            if (current[i][j] != previous[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void runSimulation(vector<vector<bool>>& grid, int rows, int cols, GameMode mode, int targetGenerations) {
    vector<vector<bool>> nextGrid(rows, vector<bool>(cols, false));
    vector<vector<bool>> previousGrid(rows, vector<bool>(cols, false));
    
    int generation = 0;
    int liveCells = countLiveCells(grid);
    bool gameWon = false;
    bool gameLost = false;
    
    cout << "Starting simulation...\n";
    cout << "Press Enter to step through, or 'a' for auto-run: ";
    char stepChoice;
    cin >> stepChoice;
    bool autoRun = (stepChoice == 'a' || stepChoice == 'A');
    
    while (generation < targetGenerations && !gameWon && !gameLost) {
        displayGrid(grid, generation, liveCells);
        
        // Check win/lose conditions based on game mode
        switch (mode) {
            case GameMode::STABILITY_GOAL:
                if (generation > 0 && isStable(grid, previousGrid)) {
                    gameWon = true;
                    cout << "🎉 WIN! Stability achieved at generation " << generation << "!\n";
                }
                break;
                
            case GameMode::SURVIVAL_GOAL:
                if (liveCells == 0) {
                    gameLost = true;
                    cout << "💀 LOSE! All cells died at generation " << generation << "!\n";
                } else if (generation >= targetGenerations - 1) {
                    gameWon = true;
                    cout << "🎉 WIN! Survived " << targetGenerations << " generations!\n";
                }
                break;
                
            case GameMode::POPULATION_TARGET:
                if (liveCells >= 20 && liveCells <= 30) {
                    if (generation >= targetGenerations - 1) {
                        gameWon = true;
                        cout << "🎉 WIN! Maintained target population for " << targetGenerations << " generations!\n";
                    }
                } else if (liveCells == 0) {
                    gameLost = true;
                    cout << "💀 LOSE! All cells died!\n";
                }
                break;
                
            case GameMode::TIME_ATTACK:
                if (liveCells == 0) {
                    gameLost = true;
                    cout << "💀 GAME OVER! Survived " << generation << " generations!\n";
                }
                break;
                
            default:
                break;
        }
        
        if (gameWon || gameLost) break;
        
        // Store current state for stability check
        previousGrid = grid;
        
        // Evolve to next generation
        evolveGrid(grid, nextGrid, rows, cols);
        generation++;
        liveCells = countLiveCells(grid);
        
        if (!autoRun) {
            cout << "Press Enter for next generation, 'q' to quit: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            char input = cin.get();
            if (input == 'q' || input == 'Q') break;
        } else {
            this_thread::sleep_for(chrono::milliseconds(DISPLAY_DELAY_MS));
        }
    }
    
    if (!gameWon && !gameLost) {
        cout << "Simulation completed after " << generation << " generations.\n";
    }
    
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Random fill grid\n";
    cout << "2. Manual setup\n";
    cout << "3. Run simulation\n";
    cout << "4. Save grid\n";
    cout << "5. Load grid\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void showGameModes() {
    cout << "\n=== Game Modes ===\n";
    cout << "1. Stability Goal - Reach a stable configuration\n";
    cout << "2. Survival Goal - Keep cells alive for N generations\n";
    cout << "3. Pattern Creation - Create specific patterns\n";
    cout << "4. Population Target - Maintain population in range\n";
    cout << "5. Time Attack - Survive as long as possible\n";
    cout << "Enter game mode: ";
}
