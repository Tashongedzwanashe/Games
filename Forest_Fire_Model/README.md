# Forest Fire Simulation Model

## Game Overview

A single-player simulation-strategy game implemented in C++ that models the spread of forest fires using cellular automata principles.

## Grid World Representation

- **T** = Tree
- **F** = Burning Tree
- **.** = Empty space

## Model Rules

### Core Simulation Rules

1. **Burning Trees**: Trees that are on fire (F) become empty spaces (.) in the next step
2. **Fire Spread**: Trees (T) catch fire if they have at least one burning neighbor
3. **Tree Regrowth**: Empty spaces (.) can regrow trees with a specified probability
4. **Lightning Strikes**: Trees can spontaneously catch fire due to lightning strikes

### Boundary Conditions

- **Periodic Boundary**: The grid wraps around at edges (toroidal surface)
- Fire can spread from one edge to the opposite edge

## Algorithm Overview

### Initialization Phase

1. User inputs grid dimensions (rows × columns)
2. User specifies initial tree density (0.0-1.0)
3. Grid is randomly populated with trees based on density
4. User chooses fire start location (center, corners, or random)
5. User sets regrowth and lightning probabilities

### Simulation Loop

1. **Synchronous Update**: All cells update simultaneously
2. **State Transitions**:
   - F → . (burning trees become empty)
   - T → F (trees catch fire from neighbors or lightning)
   - . → T (empty spaces regrow trees with probability)
3. **Neighbor Checking**: 8-neighbor connectivity with periodic boundaries

### Update Algorithm

```cpp
for each cell (i,j):
    if cell == 'F':
        newGrid[i][j] = '.'  // Burn out
    else if cell == 'T':
        if hasBurningNeighbor(i,j) || lightning():
            newGrid[i][j] = 'F'  // Catch fire
    else if cell == '.':
        if random() < regrowthProb:
            newGrid[i][j] = 'T'  // Regrow
```

## Code Structure

### Main Class: `ForestFire`

- **Private Members**:
  - `grid`: 2D vector representing the forest
  - `rows, cols`: Grid dimensions
  - `treeDensity, regrowthProb, lightningProb`: Simulation parameters
  - `stepCount`: Current simulation step
  - Random number generation objects

### Key Methods

- `initialize()`: Phase 1 - Grid setup and parameter input
- `runSimulation()`: Phase 2 - Main simulation loop
- `stepSimulation()`: Apply update rules to all cells
- `hasBurningNeighbor()`: Check 8-neighbor connectivity
- `displayGrid()`: Visualize current state
- `displayStats()`: Show current statistics

### Interactive Features (Phase 3)

- **Step-by-step mode**: Manual progression through simulation
- **Auto-run mode**: Automatic progression with configurable delay
- **Reset**: Restart simulation with new parameters

## Usage Instructions

### Compilation

```bash
g++ -std=c++11 forest_fire.cpp -o forest_fire
```

### Running the Simulation

```bash
./forest_fire
```

### Input Parameters

1. **Grid Size**: Enter rows and columns (e.g., 20 20)
2. **Tree Density**: Percentage of cells initially containing trees (e.g., 0.6 for 60%)
3. **Regrowth Probability**: Chance of empty cells growing new trees (e.g., 0.01)
4. **Lightning Probability**: Chance of trees spontaneously catching fire (e.g., 0.001)
5. **Fire Start Location**: Choose from center, corners, or random

### Interactive Commands

- **S**: Step simulation (advance one time step)
- **A**: Auto-run mode (run multiple steps with delay)
- **R**: Reset simulation
- **Q**: Quit simulation

## Sample Output

```
=== FOREST FIRE SIMULATION ===
Step: 8

TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT

Statistics:
Trees: 380 (95.0%)
Burning: 0 (0.0%)
Empty: 20 (5.0%)

Commands:
S - Step simulation
A - Auto-run
R - Reset
Q - Quit
Enter choice:
```

## Key Features Implemented

### Phase 1 - Grid & Initialization ✅

- User-configurable grid size
- Random tree population based on density
- Multiple fire start location options
- Parameter validation and defaults

### Phase 2 - Simulation Loop ✅

- Synchronous update algorithm
- Periodic boundary conditions
- Complete state transition rules
- Real-time statistics display

### Phase 3 - Interactive Features ✅

- Step-by-step and auto-run modes
- Reset functionality

### Phase 4 - Documentation ✅

- Comprehensive code comments
- Detailed README documentation
- Algorithm explanation
- Usage instructions

## Technical Implementation Details

### Random Number Generation

- Uses `mt19937` Mersenne Twister for high-quality random numbers
- Thread-safe random device seeding
- Uniform distribution for probability-based events

### Memory Management

- Efficient 2D vector representation
- Minimal memory overhead
- Proper cleanup in destructors

### User Interface

- Clear ASCII visualization
- Intuitive command system
- Real-time statistics updates
- Error handling and input validation

## Educational Value

This simulation demonstrates:

- **Cellular Automata**: Simple rules creating complex emergent behavior
- **System Dynamics**: How small changes affect overall system behavior
- **Probability Modeling**: Stochastic processes in natural systems
- **Object-Oriented Design**: Clean separation of concerns
- **Interactive Programming**: Real-time user control and visualization
