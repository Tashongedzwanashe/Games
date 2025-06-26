// Forest Fire Model
// Author: Emmanuel Mufunde - 100001936, George Kilibwa - 100002924, Ahmad Tomeh - 100001925
// Date: 24/06/2025 (1200 hours)

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

class ForestFire {
private:
    vector<vector<char>> grid;
    int rows, cols;
    double treeDensity;
    double regrowthProb;
    double lightningProb;
    int stepCount;
    
    // Random number generation
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<double> dis;
    
public:
    ForestFire() : gen(rd()), dis(0.0, 1.0), stepCount(0) {}
    
    // Phase 1: Grid & Initialization
    void initialize() {
        cout << "=== FOREST FIRE SIMULATION ===\n\n";
        
        // Get grid size
        cout << "Enter grid size (rows columns, e.g., 20 20): ";
        cin >> rows >> cols;
        
        if (rows <= 0 || cols <= 0) {
            cout << "Invalid grid size. Using default 20x20.\n";
            rows = cols = 20;
        }
        
        // Get tree density
        cout << "Enter initial tree density (0.0-1.0, e.g., 0.6 for 60%): ";
        cin >> treeDensity;
        
        if (treeDensity < 0.0 || treeDensity > 1.0) {
            cout << "Invalid density. Using default 0.6.\n";
            treeDensity = 0.6;
        }
        
        // Get regrowth probability
        cout << "Enter tree regrowth probability (0.0-1.0, e.g., 0.01): ";
        cin >> regrowthProb;
        
        if (regrowthProb < 0.0 || regrowthProb > 1.0) {
            cout << "Invalid probability. Using default 0.01.\n";
            regrowthProb = 0.01;
        }
        
        // Get lightning probability
        cout << "Enter lightning strike probability (0.0-1.0, e.g., 0.001): ";
        cin >> lightningProb;
        
        if (lightningProb < 0.0 || lightningProb > 1.0) {
            cout << "Invalid probability. Using default 0.001.\n";
            lightningProb = 0.001;
        }
        
        // Initialize grid
        grid.resize(rows, vector<char>(cols, '.'));
        
        // Populate with trees based on density
        populateTrees();
        
        // Choose fire start location
        chooseFireStart();
        
        cout << "\nForest initialized successfully!\n";
        cout << "Grid size: " << rows << "x" << cols << "\n";
        cout << "Tree density: " << (treeDensity * 100) << "%\n";
        cout << "Regrowth probability: " << (regrowthProb * 100) << "%\n";
        cout << "Lightning probability: " << (lightningProb * 100) << "%\n\n";
    }
    
    void populateTrees() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dis(gen) < treeDensity) {
                    grid[i][j] = 'T';
                }
            }
        }
    }
    
    void chooseFireStart() {
        cout << "Choose fire start location:\n";
        cout << "1. Center\n";
        cout << "2. Top-left corner\n";
        cout << "3. Top-right corner\n";
        cout << "4. Bottom-left corner\n";
        cout << "5. Bottom-right corner\n";
        cout << "6. Random location\n";
        cout << "Enter choice (1-6): ";
        
        int choice;
        cin >> choice;
        
        int startRow, startCol;
        
        switch (choice) {
            case 1: // Center
                startRow = rows / 2;
                startCol = cols / 2;
                break;
            case 2: // Top-left
                startRow = 0;
                startCol = 0;
                break;
            case 3: // Top-right
                startRow = 0;
                startCol = cols - 1;
                break;
            case 4: // Bottom-left
                startRow = rows - 1;
                startCol = 0;
                break;
            case 5: // Bottom-right
                startRow = rows - 1;
                startCol = cols - 1;
                break;
            case 6: // Random
                startRow = dis(gen) * rows;
                startCol = dis(gen) * cols;
                break;
            default:
                startRow = rows / 2;
                startCol = cols / 2;
                break;
        }
        
        // Ensure the starting position has a tree
        if (grid[startRow][startCol] == 'T') {
            grid[startRow][startCol] = 'F';
            cout << "Fire started at position (" << startRow << ", " << startCol << ")\n";
        } else {
            // Find nearest tree
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (grid[i][j] == 'T') {
                        grid[i][j] = 'F';
                        cout << "Fire started at nearest tree position (" << i << ", " << j << ")\n";
                        return;
                    }
                }
            }
        }
    }
    
    // Phase 2: Simulation Loop
    void runSimulation() {
        char choice;
        
        while (true) {
            displayGrid();
            displayStats();
            displayMenu();
            
            cin >> choice;
            
            switch (choice) {
                case 's':
                case 'S':
                    stepSimulation();
                    break;
                case 'a':
                case 'A':
                    autoRun();
                    break;
                case 'r':
                case 'R':
                    resetSimulation();
                    return;
                case 'q':
                case 'Q':
                    cout << "Simulation ended.\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }
    
    void stepSimulation() {
        vector<vector<char>> newGrid = grid;
        
        // Apply update rules
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                char current = grid[i][j];
                
                if (current == 'F') {
                    // Burning trees become empty
                    newGrid[i][j] = '.';
                } else if (current == 'T') {
                    // Check if tree catches fire
                    if (hasBurningNeighbor(i, j) || (dis(gen) < lightningProb)) {
                        newGrid[i][j] = 'F';
                    }
                } else if (current == '.') {
                    // Empty cells can regrow trees
                    if (dis(gen) < regrowthProb) {
                        newGrid[i][j] = 'T';
                    }
                }
            }
        }
        
        grid = newGrid;
        stepCount++;
    }
    
    bool hasBurningNeighbor(int row, int col) {
        // Check all 8 neighbors with periodic boundary conditions
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) continue;
                
                int ni = (row + di + rows) % rows;
                int nj = (col + dj + cols) % cols;
                
                if (grid[ni][nj] == 'F') {
                    return true;
                }
            }
        }
        return false;
    }
    
    void autoRun() {
        cout << "Enter number of steps to auto-run: ";
        int steps;
        cin >> steps;
        
        cout << "Enter delay between steps (milliseconds): ";
        int delay;
        cin >> delay;
        
        for (int i = 0; i < steps; i++) {
            stepSimulation();
            displayGrid();
            displayStats();
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
    
    void displayGrid() {
        system("cls"); // Clear screen (Windows)
        
        cout << "=== FOREST FIRE SIMULATION ===\n";
        cout << "Step: " << stepCount << "\n\n";
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                switch (grid[i][j]) {
                    case 'T':
                        cout << "T";
                        break;
                    case 'F':
                        cout << "F";
                        break;
                    case '.':
                        cout << ".";
                        break;
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    void displayStats() {
        int trees = 0, burning = 0, empty = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                switch (grid[i][j]) {
                    case 'T': trees++; break;
                    case 'F': burning++; break;
                    case '.': empty++; break;
                }
            }
        }
        
        cout << "Statistics:\n";
        cout << "Trees: " << trees << " (" << (trees * 100.0 / (rows * cols)) << "%)\n";
        cout << "Burning: " << burning << " (" << (burning * 100.0 / (rows * cols)) << "%)\n";
        cout << "Empty: " << empty << " (" << (empty * 100.0 / (rows * cols)) << "%)\n\n";
    }
    
    void displayMenu() {
        cout << "Commands:\n";
        cout << "S - Step simulation\n";
        cout << "A - Auto-run\n";
        cout << "R - Reset\n";
        cout << "Q - Quit\n";
        cout << "Enter choice: ";
    }
    
    void resetSimulation() {
        cout << "Resetting simulation...\n";
        stepCount = 0;
        initialize();
    }
};

int main() {
    ForestFire simulation;
    
    try {
        simulation.initialize();
        simulation.runSimulation();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
} 