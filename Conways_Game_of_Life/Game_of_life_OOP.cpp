// Conway's Game of Life - OOP Implementation
// This demonstrates how the same functionality could be implemented using OOP

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

// Game states enum
enum class GameMode {
    STABILITY_GOAL,
    SURVIVAL_GOAL,
    PATTERN_CREATION,
    POPULATION_TARGET,
    TIME_ATTACK
};

// Grid class to encapsulate the game board
class Grid {
private:
    vector<vector<bool>> cells;
    int rows;
    int cols;
    
public:
    // Constructor
    Grid(int r, int c) : rows(r), cols(c) {
        cells = vector<vector<bool>>(rows, vector<bool>(cols, false));
    }
    
    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    bool getCell(int row, int col) const { return cells[row][col]; }
    
    // Setters
    void setCell(int row, int col, bool alive) { cells[row][col] = alive; }
    
    // Grid operations
    void clear() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cells[i][j] = false;
            }
        }
    }
    
    void randomFill(double density = 0.3) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cells[i][j] = dis(gen) < density;
            }
        }
    }
    
    int countLiveCells() const {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (cells[i][j]) count++;
            }
        }
        return count;
    }
    
    int countLiveNeighbors(int row, int col) const {
        int count = 0;
        
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue; // Skip the cell itself
                
                int neighborRow = (row + i + rows) % rows; // Periodic boundary conditions
                int neighborCol = (col + j + cols) % cols;
                
                if (cells[neighborRow][neighborCol]) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
    bool isStable(const Grid& other) const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (cells[i][j] != other.cells[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void copyFrom(const Grid& other) {
        cells = other.cells;
    }
    
    // File operations
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << rows << " " << cols << "\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << (cells[i][j] ? "1" : "0") << " ";
            }
            file << "\n";
        }
        
        file.close();
        return true;
    }
    
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        int r, c;
        file >> r >> c;
        
        if (r != rows || c != cols) {
            return false;
        }
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int value;
                file >> value;
                cells[i][j] = (value == 1);
            }
        }
        
        file.close();
        return true;
    }
};

// Game Engine class to handle simulation logic
class GameEngine {
private:
    Grid currentGrid;
    Grid nextGrid;
    Grid previousGrid;
    int generation;
    int liveCells;
    GameMode mode;
    int targetGenerations;
    
public:
    GameEngine(int rows, int cols) 
        : currentGrid(rows, cols), nextGrid(rows, cols), previousGrid(rows, cols) {
        generation = 0;
        liveCells = 0;
        mode = GameMode::SURVIVAL_GOAL;
        targetGenerations = 50;
    }
    
    // Game setup methods
    void setGameMode(GameMode newMode, int target = 50) {
        mode = newMode;
        targetGenerations = target;
    }
    
    void randomFill(double density = 0.3) {
        currentGrid.randomFill(density);
        liveCells = currentGrid.countLiveCells();
    }
    
    void manualSetup() {
        currentGrid.clear();
        cout << "Manual setup mode. Enter coordinates (row col) for live cells.\n";
        cout << "Enter -1 -1 to finish.\n";
        
        int row, col;
        int count = 0;
        
        while (true) {
            cout << "Enter coordinates (row col): ";
            cin >> row >> col;
            
            if (row == -1 && col == -1) break;
            
            if (row >= 0 && row < currentGrid.getRows() && 
                col >= 0 && col < currentGrid.getCols()) {
                currentGrid.setCell(row, col, true);
                count++;
                cout << "Cell (" << row << "," << col << ") set to alive. Total: " << count << "\n";
            } else {
                cout << "Invalid coordinates. Please try again.\n";
            }
        }
        
        liveCells = currentGrid.countLiveCells();
        cout << "Manual setup complete. " << count << " cells set to alive.\n";
    }
    
    // Evolution methods
    void evolve() {
        // Store current state for stability check
        previousGrid.copyFrom(currentGrid);
        
        // Apply Conway's rules
        for (int i = 0; i < currentGrid.getRows(); i++) {
            for (int j = 0; j < currentGrid.getCols(); j++) {
                int neighbors = currentGrid.countLiveNeighbors(i, j);
                
                if (currentGrid.getCell(i, j)) {
                    // Live cell: survives with 2-3 neighbors
                    nextGrid.setCell(i, j, (neighbors == 2 || neighbors == 3));
                } else {
                    // Dead cell: becomes alive with exactly 3 neighbors
                    nextGrid.setCell(i, j, (neighbors == 3));
                }
            }
        }
        
        // Update current grid
        currentGrid.copyFrom(nextGrid);
        generation++;
        liveCells = currentGrid.countLiveCells();
    }
    
    // Game state checking
    bool isGameWon() const {
        switch (mode) {
            case GameMode::STABILITY_GOAL:
                return generation > 0 && currentGrid.isStable(previousGrid);
            case GameMode::SURVIVAL_GOAL:
                return generation >= targetGenerations;
            case GameMode::POPULATION_TARGET:
                return liveCells >= 20 && liveCells <= 30 && generation >= targetGenerations;
            default:
                return false;
        }
    }
    
    bool isGameLost() const {
        switch (mode) {
            case GameMode::SURVIVAL_GOAL:
            case GameMode::POPULATION_TARGET:
            case GameMode::TIME_ATTACK:
                return liveCells == 0;
            default:
                return false;
        }
    }
    
    bool isGameComplete() const {
        return generation >= targetGenerations || isGameWon() || isGameLost();
    }
    
    // Getters
    int getGeneration() const { return generation; }
    int getLiveCells() const { return liveCells; }
    const Grid& getCurrentGrid() const { return currentGrid; }
    
    // File operations
    bool saveGame(const string& filename) const {
        return currentGrid.saveToFile(filename);
    }
    
    bool loadGame(const string& filename) {
        if (currentGrid.loadFromFile(filename)) {
            liveCells = currentGrid.countLiveCells();
            generation = 0;
            return true;
        }
        return false;
    }
};

// Display class to handle visualization
class GameDisplay {
public:
    static void displayGrid(const Grid& grid, int generation, int liveCells) {
        system("cls"); // Clear screen (Windows)
        
        cout << "=== Conway's Game of Life ===\n";
        cout << "Generation: " << generation << " | Live Cells: " << liveCells << "\n\n";
        
        // Print column numbers
        cout << "   ";
        for (int j = 0; j < grid.getCols(); j++) {
            cout << (j % 10) << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < grid.getRows(); i++) {
            cout << (i < 10 ? " " : "") << i << " ";
            for (int j = 0; j < grid.getCols(); j++) {
                cout << (grid.getCell(i, j) ? "■ " : ". ");
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    static void showMenu() {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Random fill grid\n";
        cout << "2. Manual setup\n";
        cout << "3. Run simulation\n";
        cout << "4. Save grid\n";
        cout << "5. Load grid\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
    }
    
    static void showGameModes() {
        cout << "\n=== Game Modes ===\n";
        cout << "1. Stability Goal - Reach a stable configuration\n";
        cout << "2. Survival Goal - Keep cells alive for N generations\n";
        cout << "3. Pattern Creation - Create specific patterns\n";
        cout << "4. Population Target - Maintain population in range\n";
        cout << "5. Time Attack - Survive as long as possible\n";
        cout << "Enter game mode: ";
    }
};

// Main game controller class
class GameController {
private:
    GameEngine engine;
    
public:
    GameController(int rows, int cols) : engine(rows, cols) {}
    
    void run() {
        cout << "=== Conway's Game of Life (OOP Version) ===\n\n";
        
        char choice;
        do {
            GameDisplay::showMenu();
            cin >> choice;
            
            switch (choice) {
                case '1':
                    engine.randomFill();
                    break;
                case '2':
                    engine.manualSetup();
                    break;
                case '3':
                    runSimulation();
                    break;
                case '4':
                    {
                        string filename;
                        cout << "Enter filename to save: ";
                        cin >> filename;
                        if (engine.saveGame(filename)) {
                            cout << "Game saved successfully!\n";
                        } else {
                            cout << "Failed to save game.\n";
                        }
                    }
                    break;
                case '5':
                    {
                        string filename;
                        cout << "Enter filename to load: ";
                        cin >> filename;
                        if (engine.loadGame(filename)) {
                            cout << "Game loaded successfully!\n";
                        } else {
                            cout << "Failed to load game.\n";
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
                GameDisplay::displayGrid(engine.getCurrentGrid(), engine.getGeneration(), engine.getLiveCells());
            }
            
        } while (choice != '6');
    }
    
private:
    void runSimulation() {
        GameDisplay::showGameModes();
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
                targetGenerations = 100;
                cout << "Population target mode - maintain population in range!\n";
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
        
        engine.setGameMode(mode, targetGenerations);
        
        cout << "Starting simulation...\n";
        cout << "Press Enter to step through, or 'a' for auto-run: ";
        char stepChoice;
        cin >> stepChoice;
        bool autoRun = (stepChoice == 'a' || stepChoice == 'A');
        
        while (!engine.isGameComplete()) {
            GameDisplay::displayGrid(engine.getCurrentGrid(), engine.getGeneration(), engine.getLiveCells());
            
            if (engine.isGameWon()) {
                cout << "🎉 WIN! Game completed successfully!\n";
                break;
            }
            
            if (engine.isGameLost()) {
                cout << "💀 LOSE! Game over!\n";
                break;
            }
            
            engine.evolve();
            
            if (!autoRun) {
                cout << "Press Enter for next generation, 'q' to quit: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                char input = cin.get();
                if (input == 'q' || input == 'Q') break;
            } else {
                this_thread::sleep_for(chrono::milliseconds(DISPLAY_DELAY_MS));
            }
        }
        
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

// Main function
int main() {
    int rows, cols;
    cout << "Enter grid dimensions (rows columns): ";
    cin >> rows >> cols;
    
    if (rows <= 0 || cols <= 0 || rows > 100 || cols > 100) {
        cout << "Invalid dimensions. Using default 20x40.\n";
        rows = DEFAULT_ROWS;
        cols = DEFAULT_COLS;
    }
    
    GameController game(rows, cols);
    game.run();
    
    return 0;
} 