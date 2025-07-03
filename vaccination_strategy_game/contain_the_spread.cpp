// Emmanuel Mufunde 100001936
//George Kilibwa 100002924
//Ahmad Tomeh 100001925
// 2025-07-02

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Cell states
enum class CellState {
    SUSCEPTIBLE = 0,
    INFECTED = 1,
    RECOVERED = 2,
    VACCINATED = 3
};

// Cell structure
struct Cell {
    CellState state;
    int infectionTime;
    bool wasVaccinated;
    
    Cell() : state(CellState::SUSCEPTIBLE), infectionTime(0), wasVaccinated(false) {}
};

// Vaccination strategies
enum class VaccinationStrategy {
    MANUAL = 0,
    RANDOM = 1,
    RING = 2,
    HIGH_DENSITY = 3,
    GREEDY = 4
};

class VaccinationGame {
private:
    vector<vector<Cell>> grid;
    int width, height;
    int initialInfectionRate;
    double infectionProbability;
    int recoveryTime;
    int vaccinationCost;
    int infectionPenalty;
    int maxVaccinationsPerTurn;
    int totalVaccinated;
    int totalInfected;
    int totalRecovered;
    int turn;
    int totalCost;
    random_device rd;
    mt19937 gen;
    
public:
    VaccinationGame(int w, int h, int initRate, double infProb, int recTime, 
                   int vacCost, int infPenalty, int maxVac) 
        : width(w), height(h), initialInfectionRate(initRate), 
          infectionProbability(infProb), recoveryTime(recTime),
          vaccinationCost(vacCost), infectionPenalty(infPenalty),
          maxVaccinationsPerTurn(maxVac), totalVaccinated(0), 
          totalInfected(0), totalRecovered(0), turn(0), totalCost(0),
          gen(rd()) {
        
        // Initialize grid
        grid.resize(height, vector<Cell>(width));
        
        // Set initial infections
        int initialInfections = (width * height * initialInfectionRate) / 100;
        uniform_int_distribution<> disX(0, width - 1);
        uniform_int_distribution<> disY(0, height - 1);
        
        for (int i = 0; i < initialInfections; i++) {
            int x, y;
            do {
                x = disX(gen);
                y = disY(gen);
            } while (grid[y][x].state == CellState::INFECTED);
            
            grid[y][x].state = CellState::INFECTED;
            grid[y][x].infectionTime = 0;
        }
        
        updateCounts();
    }
    
    void updateCounts() {
        totalInfected = 0;
        totalVaccinated = 0;
        totalRecovered = 0;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                switch (grid[y][x].state) {
                    case CellState::INFECTED:
                        totalInfected++;
                        break;
                    case CellState::VACCINATED:
                        totalVaccinated++;
                        break;
                    case CellState::RECOVERED:
                        totalRecovered++;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    void displayGrid() {
        system("cls"); // Clear screen (Windows)
        
        cout << "=== CONTAIN THE SPREAD - Vaccination Strategy Game ===" << endl;
        cout << "Turn: " << turn << endl;
        cout << "Grid Size: " << width << "x" << height << endl;
        cout << "Infected: " << totalInfected << " | Vaccinated: " << totalVaccinated 
             << " | Recovered: " << totalRecovered << endl;
        cout << "Total Cost: $" << totalCost << " (Vaccinations: $" 
             << (totalVaccinated * vaccinationCost) << " + Infections: $" 
             << (totalInfected * infectionPenalty) << ")" << endl;
        cout << endl;
        
        // Display grid (for smaller grids)
        if (width <= 50 && height <= 30) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    switch (grid[y][x].state) {
                        case CellState::SUSCEPTIBLE:
                            cout << "S ";
                            break;
                        case CellState::INFECTED:
                            cout << "I ";
                            break;
                        case CellState::RECOVERED:
                            cout << "R ";
                            break;
                        case CellState::VACCINATED:
                            cout << "V ";
                            break;
                    }
                }
                cout << endl;
            }
        } else {
            cout << "Grid too large to display. Use statistics view." << endl;
        }
        cout << endl;
    }
    
    bool isValidPosition(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
    
    int countInfectedNeighbors(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                
                int nx = x + dx;
                int ny = y + dy;
                
                if (isValidPosition(nx, ny) && grid[ny][nx].state == CellState::INFECTED) {
                    count++;
                }
            }
        }
        return count;
    }
    
    void manualVaccination() {
        cout << "Enter cells to vaccinate (format: x y, e.g., '3 2'). Enter 'done' to finish:" << endl;
        cout << "Max vaccinations this turn: " << maxVaccinationsPerTurn << endl;
        
        int vaccinationsThisTurn = 0;
        string input;
        
        while (vaccinationsThisTurn < maxVaccinationsPerTurn) {
            cout << "> ";
            getline(cin, input);
            
            if (input == "done") break;
            
            int x, y;
            if (sscanf(input.c_str(), "%d %d", &x, &y) == 2) {
                if (isValidPosition(x, y)) {
                    if (grid[y][x].state == CellState::SUSCEPTIBLE) {
                        grid[y][x].state = CellState::VACCINATED;
                        grid[y][x].wasVaccinated = true;
                        vaccinationsThisTurn++;
                        cout << "Vaccinated cell (" << x << ", " << y << ")" << endl;
                    } else {
                        cout << "Cell (" << x << ", " << y << ") cannot be vaccinated (not susceptible)" << endl;
                    }
                } else {
                    cout << "Invalid position. Grid is " << width << "x" << height << endl;
                }
            } else {
                cout << "Invalid format. Use 'x y' or 'done'" << endl;
            }
        }
    }
    
    void randomVaccination() {
        vector<pair<int, int>> susceptibleCells;
        
        // Find all susceptible cells
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].state == CellState::SUSCEPTIBLE) {
                    susceptibleCells.push_back({x, y});
                }
            }
        }
        
        // Shuffle and vaccinate
        shuffle(susceptibleCells.begin(), susceptibleCells.end(), gen);
        
        int vaccinationsThisTurn = min(maxVaccinationsPerTurn, (int)susceptibleCells.size());
        for (int i = 0; i < vaccinationsThisTurn; i++) {
            int x = susceptibleCells[i].first;
            int y = susceptibleCells[i].second;
            grid[y][x].state = CellState::VACCINATED;
            grid[y][x].wasVaccinated = true;
        }
        
        cout << "Random strategy vaccinated " << vaccinationsThisTurn << " cells." << endl;
    }
    
    void ringVaccination() {
        vector<pair<int, int>> candidates;
        
        // Find susceptible cells adjacent to infected ones
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].state == CellState::SUSCEPTIBLE && 
                    countInfectedNeighbors(x, y) > 0) {
                    candidates.push_back({x, y});
                }
            }
        }
        
        // Sort by number of infected neighbors (descending)
        sort(candidates.begin(), candidates.end(), 
             [this](const pair<int, int>& a, const pair<int, int>& b) {
                 return countInfectedNeighbors(a.first, a.second) > 
                        countInfectedNeighbors(b.first, b.second);
             });
        
        int vaccinationsThisTurn = min(maxVaccinationsPerTurn, (int)candidates.size());
        for (int i = 0; i < vaccinationsThisTurn; i++) {
            int x = candidates[i].first;
            int y = candidates[i].second;
            grid[y][x].state = CellState::VACCINATED;
            grid[y][x].wasVaccinated = true;
        }
        
        cout << "Ring strategy vaccinated " << vaccinationsThisTurn << " cells." << endl;
    }
    
    void highDensityVaccination() {
        vector<pair<int, int>> candidates;
        
        // Find susceptible cells with high population density
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].state == CellState::SUSCEPTIBLE) {
                    int neighbors = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            
                            int nx = x + dx;
                            int ny = y + dy;
                            
                            if (isValidPosition(nx, ny) && 
                                grid[ny][nx].state != CellState::SUSCEPTIBLE) {
                                neighbors++;
                            }
                        }
                    }
                    if (neighbors >= 3) { // High density threshold
                        candidates.push_back({x, y});
                    }
                }
            }
        }
        
        shuffle(candidates.begin(), candidates.end(), gen);
        
        int vaccinationsThisTurn = min(maxVaccinationsPerTurn, (int)candidates.size());
        for (int i = 0; i < vaccinationsThisTurn; i++) {
            int x = candidates[i].first;
            int y = candidates[i].second;
            grid[y][x].state = CellState::VACCINATED;
            grid[y][x].wasVaccinated = true;
        }
        
        cout << "High-density strategy vaccinated " << vaccinationsThisTurn << " cells." << endl;
    }
    
    void greedyVaccination() {
        vector<pair<int, int>> candidates;
        
        // Find all susceptible cells
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].state == CellState::SUSCEPTIBLE) {
                    candidates.push_back({x, y});
                }
            }
        }
        
        // Sort by number of infected neighbors (descending)
        sort(candidates.begin(), candidates.end(), 
             [this](const pair<int, int>& a, const pair<int, int>& b) {
                 return countInfectedNeighbors(a.first, a.second) > 
                        countInfectedNeighbors(b.first, b.second);
             });
        
        int vaccinationsThisTurn = min(maxVaccinationsPerTurn, (int)candidates.size());
        for (int i = 0; i < vaccinationsThisTurn; i++) {
            int x = candidates[i].first;
            int y = candidates[i].second;
            grid[y][x].state = CellState::VACCINATED;
            grid[y][x].wasVaccinated = true;
        }
        
        cout << "Greedy strategy vaccinated " << vaccinationsThisTurn << " cells." << endl;
    }
    
    void spreadInfection() {
        vector<vector<Cell>> newGrid = grid;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].state == CellState::INFECTED) {
                    // Try to infect neighbors
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            
                            int nx = x + dx;
                            int ny = y + dy;
                            
                            if (isValidPosition(nx, ny) && 
                                grid[ny][nx].state == CellState::SUSCEPTIBLE) {
                                
                                uniform_real_distribution<> dis(0.0, 1.0);
                                if (dis(gen) < infectionProbability) {
                                    newGrid[ny][nx].state = CellState::INFECTED;
                                    newGrid[ny][nx].infectionTime = 0;
                                }
                            }
                        }
                    }
                    
                    // Check for recovery
                    grid[y][x].infectionTime++;
                    if (grid[y][x].infectionTime >= recoveryTime) {
                        newGrid[y][x].state = CellState::RECOVERED;
                    }
                }
            }
        }
        
        grid = newGrid;
    }
    
    void playTurn(VaccinationStrategy strategy) {
        turn++;
        displayGrid();
        
        // Vaccination phase
        cout << "--- Vaccination Phase ---" << endl;
        switch (strategy) {
            case VaccinationStrategy::MANUAL:
                manualVaccination();
                break;
            case VaccinationStrategy::RANDOM:
                randomVaccination();
                break;
            case VaccinationStrategy::RING:
                ringVaccination();
                break;
            case VaccinationStrategy::HIGH_DENSITY:
                highDensityVaccination();
                break;
            case VaccinationStrategy::GREEDY:
                greedyVaccination();
                break;
        }
        
        updateCounts();
        
        // Infection spreading phase
        cout << "--- Infection Spreading ---" << endl;
        spreadInfection();
        updateCounts();
        
        // Calculate costs
        totalCost = (totalVaccinated * vaccinationCost) + (totalInfected * infectionPenalty);
        
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    bool isGameOver() {
        return totalInfected == 0;
    }
    
    void showFinalResults() {
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Final Statistics:" << endl;
        cout << "Total Turns: " << turn << endl;
        cout << "Total Vaccinated: " << totalVaccinated << endl;
        cout << "Total Infected: " << totalInfected << endl;
        cout << "Total Recovered: " << totalRecovered << endl;
        cout << "Final Cost: $" << totalCost << endl;
        
        // Determine rank
        string rank;
        if (totalCost < 1000) {
            rank = "GOLD";
        } else if (totalCost < 2000) {
            rank = "SILVER";
        } else if (totalCost < 3000) {
            rank = "BRONZE";
        } else {
            rank = "NEEDS IMPROVEMENT";
        }
        
        cout << "Rank: " << rank << endl;
    }
    
    void runGame() {
        cout << "Welcome to 'Contain the Spread' - Vaccination Strategy Game!" << endl;
        cout << "Choose vaccination strategy:" << endl;
        cout << "1. Manual" << endl;
        cout << "2. Random" << endl;
        cout << "3. Ring Vaccination" << endl;
        cout << "4. High-Density Targeting" << endl;
        cout << "5. Greedy Strategy" << endl;
        
        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore();
        
        VaccinationStrategy strategy = static_cast<VaccinationStrategy>(choice - 1);
        
        while (!isGameOver()) {
            playTurn(strategy);
        }
        
        showFinalResults();
    }
};

int main() {
    cout << "=== CONTAIN THE SPREAD - Vaccination Strategy Game ===" << endl;
    cout << "Configure your simulation:" << endl;
    
    int width, height, initRate, recTime, vacCost, infPenalty, maxVac;
    double infProb;
    
    cout << "Grid width: ";
    cin >> width;
    cout << "Grid height: ";
    cin >> height;
    cout << "Initial infection rate (%): ";
    cin >> initRate;
    cout << "Infection probability (0.0-1.0): ";
    cin >> infProb;
    cout << "Recovery time (turns): ";
    cin >> recTime;
    cout << "Vaccination cost per person: ";
    cin >> vacCost;
    cout << "Infection penalty per person: ";
    cin >> infPenalty;
    cout << "Max vaccinations per turn: ";
    cin >> maxVac;
    
    VaccinationGame game(width, height, initRate, infProb, recTime, 
                        vacCost, infPenalty, maxVac);
    
    game.runGame();
    
    return 0;
} 