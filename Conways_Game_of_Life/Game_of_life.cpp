// Conway's Game of Life Implementation
// Authors: Mufunde Emmanuel-100001936, George Kilibwa - 100002624, Riad Al Zaim- 100003048
// Date: 19/06/2025 (1725)
// Description: A cellular automaton simulation with automatic win condition detection

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <limits>
#include <map>
using namespace std;

// Game configuration constants
const int DEFAULT_ROWS = 20;
const int DEFAULT_COLS = 40;
const int MAX_GENERATIONS = 1000;
const int DISPLAY_DELAY_MS = 500;

// Win condition tracking
struct WinCondition {
    bool achieved = false;
    int generation = 0;
    string description;
};

struct GameStats {
    int generation = 0;
    int liveCells = 0;
    int maxLiveCells = 0;
    int minLiveCells = 0;
    int stabilityCount = 0;
    int populationInRangeCount = 0;
    bool hasOscillated = false;
    vector<int> populationHistory;
    
    // Win conditions
    map<string, WinCondition> winConditions;
    
    GameStats() {
        // Initialize all possible win conditions
        winConditions["stability"] = {false, 0, "Stability Goal - Reached a stable configuration"};
        winConditions["survival_10"] = {false, 0, "Survival Goal - Kept cells alive for 10 generations"};
        winConditions["survival_25"] = {false, 0, "Survival Goal - Kept cells alive for 25 generations"};
        winConditions["survival_50"] = {false, 0, "Survival Goal - Kept cells alive for 50 generations"};
        winConditions["survival_100"] = {false, 0, "Survival Goal - Kept cells alive for 100 generations"};
        winConditions["population_balance"] = {false, 0, "Population Target - Maintained balanced population (20-30) for 20 generations"};
        winConditions["glider_pattern"] = {false, 0, "Pattern Creation - Created a glider pattern"};
        winConditions["blinker_pattern"] = {false, 0, "Pattern Creation - Created a blinker pattern"};
        winConditions["block_pattern"] = {false, 0, "Pattern Creation - Created a block pattern"};
        winConditions["time_attack_100"] = {false, 0, "Time Attack - Survived 100+ generations"};
        winConditions["time_attack_500"] = {false, 0, "Time Attack - Survived 500+ generations"};
    }
};

// Function declarations
void initializeGrid(vector<vector<bool>>& grid, int rows, int cols);
void displayGrid(const vector<vector<bool>>& grid, const GameStats& stats);
void randomFill(vector<vector<bool>>& grid, double density = 0.3);
void manualSetup(vector<vector<bool>>& grid);
int countLiveNeighbors(const vector<vector<bool>>& grid, int row, int col, int rows, int cols);
void evolveGrid(vector<vector<bool>>& grid, vector<vector<bool>>& nextGrid, int rows, int cols);
void saveGrid(const vector<vector<bool>>& grid, const string& filename);
bool loadGrid(vector<vector<bool>>& grid, const string& filename);
int countLiveCells(const vector<vector<bool>>& grid);
bool isStable(const vector<vector<bool>>& current, const vector<vector<bool>>& previous);
bool detectPatterns(const vector<vector<bool>>& grid, GameStats& stats);
void updateGameStats(vector<vector<bool>>& grid, vector<vector<bool>>& previousGrid, GameStats& stats);
void checkWinConditions(GameStats& stats);
void showWinSummary(const GameStats& stats);
void runAutoDetectSimulation(vector<vector<bool>>& grid, int rows, int cols);
void showMenu();

int main() {
    cout << "=== Conway's Game of Life - Auto-Detect Mode ===\n\n";
    
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
                runAutoDetectSimulation(grid, rows, cols);
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
            GameStats tempStats;
            tempStats.liveCells = countLiveCells(grid);
            displayGrid(grid, tempStats);
        }
        
    } while (choice != '6');
    
    return 0;
}

void runAutoDetectSimulation(vector<vector<bool>>& grid, int rows, int cols) {
    vector<vector<bool>> nextGrid(rows, vector<bool>(cols, false));
    vector<vector<bool>> previousGrid(rows, vector<bool>(cols, false));
    
    GameStats stats;
    stats.liveCells = countLiveCells(grid);
    stats.maxLiveCells = stats.liveCells;
    stats.minLiveCells = stats.liveCells;
    
    cout << "Starting Auto-Detect Simulation...\n";
    cout << "The game will automatically detect when you achieve any win condition!\n\n";
    cout << "Press Enter to step through, or 'a' for auto-run: ";
    char stepChoice;
    cin >> stepChoice;
    bool autoRun = (stepChoice == 'a' || stepChoice == 'A');
    
    bool gameEnded = false;
    
    while (stats.generation < MAX_GENERATIONS && !gameEnded) {
        displayGrid(grid, stats);
        
        // Check for game end conditions
        if (stats.liveCells == 0) {
            cout << "💀 GAME OVER! All cells died at generation " << stats.generation << "!\n";
            gameEnded = true;
            break;
        }
        
        // Update game statistics
        updateGameStats(grid, previousGrid, stats);
        
        // Check for win conditions
        checkWinConditions(stats);
        
        // Check if any win condition was achieved
        bool anyWin = false;
        for (const auto& win : stats.winConditions) {
            if (win.second.achieved) {
                anyWin = true;
                break;
            }
        }
        
        if (anyWin) {
            showWinSummary(stats);
            gameEnded = true;
            break;
        }
        
        // Store current state for stability check
        previousGrid = grid;
        
        // Evolve to next generation
        evolveGrid(grid, nextGrid, rows, cols);
        stats.generation++;
        stats.liveCells = countLiveCells(grid);
        
        // Update population history
        stats.populationHistory.push_back(stats.liveCells);
        if (stats.populationHistory.size() > 100) {
            stats.populationHistory.erase(stats.populationHistory.begin());
        }
        
        if (!autoRun) {
            cout << "Press Enter for next generation, 'q' to quit: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            char input = cin.get();
            if (input == 'q' || input == 'Q') break;
        } else {
            this_thread::sleep_for(chrono::milliseconds(DISPLAY_DELAY_MS));
        }
    }
    
    if (!gameEnded) {
        cout << "Simulation completed after " << stats.generation << " generations.\n";
        showWinSummary(stats);
    }
    
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void updateGameStats(vector<vector<bool>>& grid, vector<vector<bool>>& previousGrid, GameStats& stats) {
    // Update max/min live cells
    if (stats.liveCells > stats.maxLiveCells) {
        stats.maxLiveCells = stats.liveCells;
    }
    if (stats.liveCells < stats.minLiveCells) {
        stats.minLiveCells = stats.liveCells;
    }
    
    // Check for stability
    if (stats.generation > 0 && isStable(grid, previousGrid)) {
        stats.stabilityCount++;
    } else {
        stats.stabilityCount = 0;
    }
    
    // Check for population in target range
    if (stats.liveCells >= 20 && stats.liveCells <= 30) {
        stats.populationInRangeCount++;
    } else {
        stats.populationInRangeCount = 0;
    }
    
    // Detect patterns
    detectPatterns(grid, stats);
}

void checkWinConditions(GameStats& stats) {
    // Stability Goal
    if (stats.stabilityCount >= 3 && !stats.winConditions["stability"].achieved) {
        stats.winConditions["stability"].achieved = true;
        stats.winConditions["stability"].generation = stats.generation;
    }
    
    // Survival Goals
    if (stats.generation >= 10 && !stats.winConditions["survival_10"].achieved) {
        stats.winConditions["survival_10"].achieved = true;
        stats.winConditions["survival_10"].generation = stats.generation;
    }
    if (stats.generation >= 25 && !stats.winConditions["survival_25"].achieved) {
        stats.winConditions["survival_25"].achieved = true;
        stats.winConditions["survival_25"].generation = stats.generation;
    }
    if (stats.generation >= 50 && !stats.winConditions["survival_50"].achieved) {
        stats.winConditions["survival_50"].achieved = true;
        stats.winConditions["survival_50"].generation = stats.generation;
    }
    if (stats.generation >= 100 && !stats.winConditions["survival_100"].achieved) {
        stats.winConditions["survival_100"].achieved = true;
        stats.winConditions["survival_100"].generation = stats.generation;
    }
    
    // Population Target
    if (stats.populationInRangeCount >= 20 && !stats.winConditions["population_balance"].achieved) {
        stats.winConditions["population_balance"].achieved = true;
        stats.winConditions["population_balance"].generation = stats.generation;
    }
    
    // Time Attack
    if (stats.generation >= 100 && !stats.winConditions["time_attack_100"].achieved) {
        stats.winConditions["time_attack_100"].achieved = true; 
        stats.winConditions["time_attack_100"].generation = stats.generation;
    }
    if (stats.generation >= 500 && !stats.winConditions["time_attack_500"].achieved) {
        stats.winConditions["time_attack_500"].achieved = true;
        stats.winConditions["time_attack_500"].generation = stats.generation;
    }
}

bool detectPatterns(const vector<vector<bool>>& grid, GameStats& stats) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Check for glider pattern (simplified detection)
    for (int i = 0; i < rows - 2; i++) {
        for (int j = 0; j < cols - 2; j++) {
            // Simple glider detection (5 cells in specific pattern)
            int liveCount = 0;
            if (grid[i][j+1]) liveCount++;
            if (grid[i+1][j+2]) liveCount++;
            if (grid[i+2][j]) liveCount++;
            if (grid[i+2][j+1]) liveCount++;
            if (grid[i+2][j+2]) liveCount++;
            
            if (liveCount == 5 && !stats.winConditions["glider_pattern"].achieved) {
                stats.winConditions["glider_pattern"].achieved = true;
                stats.winConditions["glider_pattern"].generation = stats.generation;
                return true;
            }
        }
    }
    
    // Check for blinker pattern (3 cells in a row or column)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 2; j++) {
            if (grid[i][j] && grid[i][j+1] && grid[i][j+2] && 
                !grid[i][j-1] && !grid[i][j+3]) {
                if (!stats.winConditions["blinker_pattern"].achieved) {
                    stats.winConditions["blinker_pattern"].achieved = true;
                    stats.winConditions["blinker_pattern"].generation = stats.generation;
                    return true;
                }
            }
        }
    }
    
    // Check for block pattern (2x2 square)
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            if (grid[i][j] && grid[i][j+1] && grid[i+1][j] && grid[i+1][j+1]) {
                if (!stats.winConditions["block_pattern"].achieved) {
                    stats.winConditions["block_pattern"].achieved = true;
                    stats.winConditions["block_pattern"].generation = stats.generation;
                    return true;
                }
            }
        }
    }
    
    return false;
}

void showWinSummary(const GameStats& stats) {
    cout << "\n🎉 WIN CONDITION SUMMARY 🎉\n";
    cout << "=============================\n";
    
    bool anyWin = false;
    for (const auto& win : stats.winConditions) {
        if (win.second.achieved) {
            cout << "✅ " << win.second.description;
            cout << " (Generation " << win.second.generation << ")\n";
            anyWin = true;
        }
    }
    
    if (!anyWin) {
        cout << "No win conditions achieved yet.\n";
    }
    
    cout << "\n📊 Final Statistics:\n";
    cout << "Total Generations: " << stats.generation << "\n";
    cout << "Final Live Cells: " << stats.liveCells << "\n";
    cout << "Max Live Cells: " << stats.maxLiveCells << "\n";
    cout << "Min Live Cells: " << stats.minLiveCells << "\n";
    cout << "=============================\n";
}

void initializeGrid(vector<vector<bool>>& grid, int rows, int cols) {
    // Grid is already initialized with false values
    cout << "Grid initialized with " << rows << "x" << cols << " dimensions.\n";
}

void displayGrid(const vector<vector<bool>>& grid, const GameStats& stats) {
    system("cls"); // Clear screen (Windows)
    
    cout << "=== Conway's Game of Life - Auto-Detect Mode ===\n";
    cout << "Generation: " << stats.generation << " | Live Cells: " << stats.liveCells << "\n";
    cout << "Max/Min Population: " << stats.maxLiveCells << "/" << stats.minLiveCells << "\n";
    
    // Show active win conditions
    cout << "Active Win Conditions: ";
    bool anyActive = false;
    for (const auto& win : stats.winConditions) {
        if (win.second.achieved) {
            cout << "✅ ";
            anyActive = true;
        }
    }
    if (!anyActive) cout << "None yet";
    cout << "\n\n";
    
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

void showMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Random fill grid\n";
    cout << "2. Manual setup\n";
    cout << "3. Run auto-detect simulation\n";
    cout << "4. Save grid\n";
    cout << "5. Load grid\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}
