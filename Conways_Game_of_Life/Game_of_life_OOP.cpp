// Conway's Game of Life - OOP Implementation (Console Version with GUI Manual Setup)
// This demonstrates how the same functionality could be implemented using OOP

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <limits>
#include <SFML/Graphics.hpp>
#include <variant>
using namespace std;

// Game configuration constants
const int DEFAULT_ROWS = 20;
const int DEFAULT_COLS = 40;
const int MAX_GENERATIONS = 1000;
const int DISPLAY_DELAY_MS = 500;
const int CELL_SIZE = 20;  // Size of each cell in pixels
const int WINDOW_PADDING = 50;  // Padding around the grid
const int TEXT_HEIGHT = 120;  // Height reserved for text instructions
const int GRID_BORDER = 2;  // Border around the grid

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

// Graphical Manual Setup class
class ManualSetupWindow {
private:
    sf::RenderWindow window;
    Grid& grid;
    sf::Font font;
    bool fontLoaded;
    
public:
    ManualSetupWindow(Grid& g) : grid(g) {
        int gridPixelHeight = grid.getRows() * CELL_SIZE + 2 * WINDOW_PADDING + GRID_BORDER * 2;
        int minTextHeight = TEXT_HEIGHT + 40; // Extra space for text and padding
        int minWindowHeight = 400; // Minimum window height for small grids
        int windowHeight = std::max(gridPixelHeight + minTextHeight, minWindowHeight);
        int windowWidth = grid.getCols() * CELL_SIZE + 2 * WINDOW_PADDING + GRID_BORDER * 2;
        
        // SFML 3.0 uses Vector2u for VideoMode
        window.create(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Manual Setup - Conway's Game of Life");
        window.setFramerateLimit(60);
        
        // Try to load font - SFML 3.0 uses openFromFile
        fontLoaded = font.openFromFile("arial.ttf");
        if (!fontLoaded) {
            // Try alternative fonts
            fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");
        }
    }
    
    bool run() {
        while (window.isOpen()) {
            if (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return false;
                }
                if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouse->button == sf::Mouse::Button::Left) {
                        handleMouseClick(mouse->position.x, mouse->position.y);
                    }
                }
                if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                    if (key->code == sf::Keyboard::Key::S) {
                        window.close();
                        return true;
                    }
                    if (key->code == sf::Keyboard::Key::Escape) {
                        window.close();
                        return false;
                    }
                }
            }
            render();
        }
        return false;
    }
    
private:
    void handleMouseClick(int mouseX, int mouseY) {
        // Calculate grid position from mouse coordinates
        int gridX = (mouseX - WINDOW_PADDING) / CELL_SIZE;
        int gridY = (mouseY - WINDOW_PADDING) / CELL_SIZE;
        
        // Check if click is within grid bounds
        if (gridX >= 0 && gridX < grid.getCols() && 
            gridY >= 0 && gridY < grid.getRows()) {
            // Toggle cell state
            bool currentState = grid.getCell(gridY, gridX);
            grid.setCell(gridY, gridX, !currentState);
        }
    }
    
    void render() {
        // Modern gradient-like background
        window.clear(sf::Color(245, 247, 250)); // Light blue-gray background
        
        // Draw title bar background
        sf::RectangleShape titleBar(sf::Vector2f(window.getSize().x, 60));
        titleBar.setPosition(sf::Vector2f(0, 0));
        titleBar.setFillColor(sf::Color(52, 73, 94)); // Dark blue-gray
        window.draw(titleBar);
        
        // Draw grid border
        sf::RectangleShape gridBorder(sf::Vector2f(
            grid.getCols() * CELL_SIZE + GRID_BORDER * 2,
            grid.getRows() * CELL_SIZE + GRID_BORDER * 2
        ));
        gridBorder.setPosition(sf::Vector2f(WINDOW_PADDING - GRID_BORDER, WINDOW_PADDING - GRID_BORDER));
        gridBorder.setFillColor(sf::Color(189, 195, 199)); // Light gray border
        gridBorder.setOutlineColor(sf::Color(149, 165, 166)); // Darker gray outline
        gridBorder.setOutlineThickness(2);
        window.draw(gridBorder);
        
        // Draw grid cells with improved styling
        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                cell.setPosition(sf::Vector2f(WINDOW_PADDING + j * CELL_SIZE, WINDOW_PADDING + i * CELL_SIZE));
                
                if (grid.getCell(i, j)) {
                    // Live cell with gradient effect
                    cell.setFillColor(sf::Color(46, 204, 113)); // Green for live cells
                    cell.setOutlineColor(sf::Color(39, 174, 96)); // Darker green outline
                    cell.setOutlineThickness(1);
                } else {
                    // Dead cell with subtle styling
                    cell.setFillColor(sf::Color(236, 240, 241)); // Very light gray
                    cell.setOutlineColor(sf::Color(189, 195, 199)); // Light gray outline
                    cell.setOutlineThickness(0.5f);
                }
                
                window.draw(cell);
            }
        }
        
        // Calculate Y position for the instructions panel and text
        int panelY = window.getSize().y - TEXT_HEIGHT + 10;
        // Draw instructions panel background
        sf::RectangleShape instructionPanel(sf::Vector2f(window.getSize().x - 20, TEXT_HEIGHT - 20));
        instructionPanel.setPosition(sf::Vector2f(10, panelY));
        instructionPanel.setFillColor(sf::Color(255, 255, 255)); // White background
        instructionPanel.setOutlineColor(sf::Color(189, 195, 199)); // Light gray border
        instructionPanel.setOutlineThickness(1);
        window.draw(instructionPanel);
        
        // Draw text elements
        if (fontLoaded) {
            // Title
            sf::Text title(font, "Manual Setup - Conway's Game of Life");
            title.setCharacterSize(18);
            title.setFillColor(sf::Color::White);
            title.setPosition(sf::Vector2f(20, 20));
            window.draw(title);
            
            // Instructions
            sf::Text instructions(font, "Click cells to toggle them alive/dead");
            instructions.setCharacterSize(14);
            instructions.setFillColor(sf::Color(52, 73, 94)); // Dark blue-gray
            instructions.setPosition(sf::Vector2f(20, panelY + 10));
            window.draw(instructions);
            
            // Controls
            sf::Text controls(font, "Controls: Press 'S' to save | Press 'ESC' to cancel");
            controls.setCharacterSize(12);
            controls.setFillColor(sf::Color(149, 165, 166)); // Medium gray
            controls.setPosition(sf::Vector2f(20, panelY + 35));
            window.draw(controls);
            
            // Live cell count with better styling
            sf::Text cellCountLabel(font, "Live Cells:");
            cellCountLabel.setCharacterSize(12);
            cellCountLabel.setFillColor(sf::Color(149, 165, 166)); // Medium gray
            cellCountLabel.setPosition(sf::Vector2f(20, panelY + 60));
            window.draw(cellCountLabel);
            
            sf::Text cellCount(font, to_string(grid.countLiveCells()));
            cellCount.setCharacterSize(16);
            cellCount.setFillColor(sf::Color(46, 204, 113)); // Green color
            cellCount.setPosition(sf::Vector2f(100, panelY + 58));
            window.draw(cellCount);
            
            // Grid size info
            sf::Text gridInfo(font, "Grid: " + to_string(grid.getRows()) + "x" + to_string(grid.getCols()));
            gridInfo.setCharacterSize(12);
            gridInfo.setFillColor(sf::Color(149, 165, 166)); // Medium gray
            gridInfo.setPosition(sf::Vector2f(200, panelY + 60));
            window.draw(gridInfo);
        }
        
        window.display();
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
    
    bool manualSetup() {
        currentGrid.clear();
        cout << "Opening manual setup window...\n";
        cout << "Click cells to toggle them alive/dead.\n";
        cout << "Press 'S' to save or 'ESC' to cancel.\n";
        
        ManualSetupWindow setupWindow(currentGrid);
        bool saved = setupWindow.run();
        
        if (saved) {
            liveCells = currentGrid.countLiveCells();
            cout << "Manual setup complete. " << liveCells << " cells set to alive.\n";
        } else {
            cout << "Manual setup cancelled.\n";
        }
        
        return saved;
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
    
    // Get detailed end-game information
    string getEndGameMessage() const {
        if (isGameWon()) {
            switch (mode) {
                case GameMode::STABILITY_GOAL:
                    return "🎉 WIN! You achieved a stable configuration after " + to_string(generation) + " generations!";
                case GameMode::SURVIVAL_GOAL:
                    return "🎉 WIN! You survived for " + to_string(generation) + " generations (target: " + to_string(targetGenerations) + ")!";
                case GameMode::POPULATION_TARGET:
                    return "🎉 WIN! You maintained population in range (20-30) for " + to_string(generation) + " generations!";
                case GameMode::PATTERN_CREATION:
                    return "🎉 WIN! You successfully created a pattern that survived for " + to_string(generation) + " generations!";
                case GameMode::TIME_ATTACK:
                    return "🎉 WIN! You survived for " + to_string(generation) + " generations in time attack mode!";
                default:
                    return "🎉 WIN! Game completed successfully!";
            }
        } else if (isGameLost()) {
            switch (mode) {
                case GameMode::SURVIVAL_GOAL:
                    return "💀 LOSE! All cells died after " + to_string(generation) + " generations (target: " + to_string(targetGenerations) + ").";
                case GameMode::POPULATION_TARGET:
                    return "💀 LOSE! All cells died after " + to_string(generation) + " generations. Population target was 20-30 cells.";
                case GameMode::TIME_ATTACK:
                    return "💀 LOSE! All cells died after " + to_string(generation) + " generations in time attack mode.";
                default:
                    return "💀 LOSE! All cells died after " + to_string(generation) + " generations.";
            }
        } else if (generation >= targetGenerations) {
            switch (mode) {
                case GameMode::STABILITY_GOAL:
                    return "⏰ TIME'S UP! Reached " + to_string(targetGenerations) + " generations without achieving stability. Final population: " + to_string(liveCells) + " cells.";
                case GameMode::POPULATION_TARGET:
                    return "⏰ TIME'S UP! Reached " + to_string(targetGenerations) + " generations. Final population: " + to_string(liveCells) + " cells (target: 20-30).";
                case GameMode::PATTERN_CREATION:
                    return "⏰ TIME'S UP! Reached " + to_string(targetGenerations) + " generations. Final population: " + to_string(liveCells) + " cells.";
                default:
                    return "⏰ TIME'S UP! Reached " + to_string(targetGenerations) + " generations. Final population: " + to_string(liveCells) + " cells.";
            }
        } else {
            return "Simulation ended. Final population: " + to_string(liveCells) + " cells after " + to_string(generation) + " generations.";
        }
    }
    
    // Get current game mode name
    string getGameModeName() const {
        switch (mode) {
            case GameMode::STABILITY_GOAL: return "Stability Goal";
            case GameMode::SURVIVAL_GOAL: return "Survival Goal";
            case GameMode::PATTERN_CREATION: return "Pattern Creation";
            case GameMode::POPULATION_TARGET: return "Population Target";
            case GameMode::TIME_ATTACK: return "Time Attack";
            default: return "Unknown";
        }
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
                cout << (grid.getCell(i, j) ? "O " : ". ");
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    static void showMenu() {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Random fill grid\n";
        cout << "2. Manual setup (GUI)\n";
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
        cout << "=== Conway's Game of Life (OOP Console Version with GUI Manual Setup) ===\n\n";
        
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
        
        cout << "\n=== Starting " << engine.getGameModeName() << " Mode ===\n";
        cout << "Target: " << targetGenerations << " generations\n";
        cout << "Starting simulation...\n";
        cout << "Press Enter to step through, or 'a' for auto-run: ";
        char stepChoice;
        cin >> stepChoice;
        bool autoRun = (stepChoice == 'a' || stepChoice == 'A');
        
        while (!engine.isGameComplete()) {
            GameDisplay::displayGrid(engine.getCurrentGrid(), engine.getGeneration(), engine.getLiveCells());
            
            if (engine.isGameWon()) {
                cout << "\n" << engine.getEndGameMessage() << "\n";
                break;
            }
            
            if (engine.isGameLost()) {
                cout << "\n" << engine.getEndGameMessage() << "\n";
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
        
        // Show final result if simulation ended due to time limit
        if (!engine.isGameWon() && !engine.isGameLost() && engine.getGeneration() >= targetGenerations) {
            cout << "\n" << engine.getEndGameMessage() << "\n";
        }
        
        cout << "\nPress Enter to continue...";
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