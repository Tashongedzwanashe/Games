# Contain the Spread - Technical Documentation

## 📋 Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [Data Structures](#data-structures)
3. [Algorithms](#algorithms)
4. [Game Flow](#game-flow)
5. [Vaccination Strategies](#vaccination-strategies)
6. [SIR Dynamics Implementation](#sir-dynamics-implementation)
7. [Performance Considerations](#performance-considerations)
8. [Code Structure](#code-structure)
9. [Testing and Validation](#testing-and-validation)

## 🏗️ Architecture Overview

The game follows an object-oriented design with a single `VaccinationGame` class that encapsulates all game logic. The architecture is modular and easily extensible.

### Core Components

- **Grid Management**: 2D vector representation of the simulation space
- **State Management**: Cell states and infection tracking
- **Strategy System**: Pluggable vaccination strategies
- **SIR Engine**: Disease spread simulation
- **Cost Calculation**: Economic model for scoring

## 📊 Data Structures

### Cell Structure

```cpp
struct Cell {
    CellState state;        // Current state (S/I/R/V)
    int infectionTime;      // Time since infection
    bool wasVaccinated;     // Vaccination history
};
```

### Cell States

```cpp
enum class CellState {
    SUSCEPTIBLE = 0,    // Can be infected
    INFECTED = 1,       // Currently infected
    RECOVERED = 2,      // Immune after recovery
    VACCINATED = 3      // Protected by vaccination
};
```

### Vaccination Strategies

```cpp
enum class VaccinationStrategy {
    MANUAL = 0,         // User input
    RANDOM = 1,         // Random selection
    RING = 2,           // Around infected
    HIGH_DENSITY = 3,   // Crowded areas
    GREEDY = 4          // Optimal blocking
};
```

## 🧮 Algorithms

### Infection Spread Algorithm

```cpp
void spreadInfection() {
    vector<vector<Cell>> newGrid = grid;

    for (each infected cell) {
        // Try to infect neighbors
        for (each neighbor) {
            if (neighbor is susceptible) {
                if (random < infectionProbability) {
                    infect neighbor
                }
            }
        }

        // Check for recovery
        if (infectionTime >= recoveryTime) {
            recover cell
        }
    }

    grid = newGrid;
}
```

### Neighbor Counting Algorithm

```cpp
int countInfectedNeighbors(int x, int y) {
    int count = 0;
    for (Moore neighborhood: 8 neighbors) {
        if (neighbor is infected) {
            count++;
        }
    }
    return count;
}
```

## 🎮 Game Flow

### Main Game Loop

1. **Display Current State**: Show grid and statistics
2. **Vaccination Phase**: Apply chosen strategy
3. **Infection Phase**: Spread disease using SIR rules
4. **Recovery Phase**: Update infection timers
5. **Cost Calculation**: Update scoring
6. **Check Game Over**: Continue or end

### Turn Structure

```
Turn N:
├── Display Grid & Stats
├── Vaccination Phase
│   ├── Apply Strategy
│   └── Update Counts
├── Infection Phase
│   ├── Spread Disease
│   └── Update Recovery
└── Calculate Costs
```

## 💉 Vaccination Strategies

### 1. Manual Strategy

- **Input**: User coordinates (x, y)
- **Validation**: Check bounds and susceptibility
- **Complexity**: O(1) per vaccination
- **Use Case**: Learning and testing

### 2. Random Strategy

- **Algorithm**: Shuffle susceptible cells, vaccinate first N
- **Complexity**: O(S log S) where S = susceptible count
- **Randomization**: Uses Mersenne Twister
- **Use Case**: Baseline comparison

### 3. Ring Vaccination

- **Algorithm**: Find susceptible cells adjacent to infected
- **Sorting**: By number of infected neighbors (descending)
- **Complexity**: O(S log S) for sorting
- **Use Case**: Containment strategy

### 4. High-Density Targeting

- **Algorithm**: Find susceptible cells with ≥3 non-susceptible neighbors
- **Threshold**: Configurable density requirement
- **Complexity**: O(S) for scanning
- **Use Case**: Urban/crowded scenarios

### 5. Greedy Strategy

- **Algorithm**: Vaccinate susceptible cells with most infected neighbors
- **Sorting**: By infected neighbor count (descending)
- **Complexity**: O(S log S) for sorting
- **Use Case**: Optimal containment

## 🦠 SIR Dynamics Implementation

### State Transitions

```
SUSCEPTIBLE → INFECTED (via infection)
INFECTED → RECOVERED (after recovery time)
SUSCEPTIBLE → VACCINATED (via vaccination)
```

### Infection Mechanics

- **Neighborhood**: Moore neighborhood (8 neighbors)
- **Probability**: Configurable per-neighbor infection chance
- **Timing**: Synchronous updates (all infections happen simultaneously)

### Recovery Mechanics

- **Timer**: Each infected cell tracks infection duration
- **Threshold**: Configurable recovery time
- **Permanence**: Recovered cells stay immune

## ⚡ Performance Considerations

### Memory Usage

- **Grid Storage**: O(W × H) for grid size W×H
- **Temporary Arrays**: O(W × H) for infection updates
- **Strategy Arrays**: O(S) where S = susceptible count

### Time Complexity

- **Per Turn**: O(W × H) for infection spread
- **Vaccination**: O(S log S) for sorting strategies
- **Display**: O(W × H) for grid rendering

### Optimization Techniques

- **Efficient Random**: Mersenne Twister for quality random numbers
- **Vector Operations**: Use of STL containers for efficiency
- **Minimal Allocations**: Reuse temporary vectors
- **Early Termination**: Stop when no infections remain

## 🏛️ Code Structure

### Class Organization

```cpp
class VaccinationGame {
private:
    // Data members
    vector<vector<Cell>> grid;
    int width, height;
    // ... other members

public:
    // Constructor and initialization
    VaccinationGame(...);

    // Core game methods
    void playTurn(VaccinationStrategy strategy);
    bool isGameOver();
    void runGame();

    // Strategy implementations
    void manualVaccination();
    void randomVaccination();
    void ringVaccination();
    void highDensityVaccination();
    void greedyVaccination();

    // Utility methods
    void displayGrid();
    void updateCounts();
    void spreadInfection();
    // ... other utilities
};
```

### Method Responsibilities

- **Grid Management**: `updateCounts()`, `isValidPosition()`
- **Display**: `displayGrid()`, `showFinalResults()`
- **Disease Logic**: `spreadInfection()`, `countInfectedNeighbors()`
- **Strategy Logic**: Individual vaccination methods
- **Game Control**: `playTurn()`, `runGame()`, `isGameOver()`

## 🧪 Testing and Validation

### Parameter Validation

- **Grid Size**: Positive integers, reasonable limits
- **Probabilities**: 0.0 to 1.0 range
- **Costs**: Positive integers
- **Rates**: Percentage values (0-100)

### Edge Cases

- **Empty Grid**: No cells to infect
- **Full Infection**: All cells infected initially
- **High Vaccination**: All cells vaccinated
- **Zero Recovery Time**: Immediate recovery

### Validation Checks

```cpp
// Grid bounds checking
if (!isValidPosition(x, y)) return false;

// State transitions
if (grid[y][x].state != CellState::SUSCEPTIBLE) return false;

// Cost calculations
totalCost = (totalVaccinated * vaccinationCost) +
           (totalInfected * infectionPenalty);
```

## 🔧 Configuration Parameters

### Game Parameters

- **Grid Dimensions**: width × height
- **Initial Infection Rate**: Percentage of initially infected cells
- **Infection Probability**: Chance per neighbor per turn
- **Recovery Time**: Turns until recovery
- **Vaccination Cost**: Cost per vaccination
- **Infection Penalty**: Cost per infection
- **Max Vaccinations**: Limit per turn

### Recommended Values

- **Small Grid**: 10×10 to 20×20
- **Medium Grid**: 50×50 to 100×100
- **Large Grid**: 200×200 to 1000×1000
- **Infection Rate**: 1% to 10%
- **Infection Probability**: 0.125 to 0.25
- **Recovery Time**: 2 to 5 turns

## 🚀 Extension Points

### Easy Extensions

- **New Strategies**: Add to VaccinationStrategy enum
- **Different Grid Shapes**: Modify neighbor counting
- **Multiple Diseases**: Add disease type to Cell
- **Vaccine Efficacy**: Add effectiveness parameter

### Advanced Extensions

- **Movement**: Add position tracking and movement
- **Networks**: Replace grid with graph structure
- **Multiple Strains**: Different infection properties
- **Contact Tracing**: Track infection sources

### Performance Extensions

- **Parallel Processing**: Multi-threaded infection spread
- **Spatial Indexing**: Quadtree for large grids
- **GPU Acceleration**: CUDA/OpenCL implementation
- **Memory Pooling**: Custom allocators for cells

---

This documentation provides a comprehensive overview of the game's technical implementation. For questions or contributions, refer to the main README.md file.
