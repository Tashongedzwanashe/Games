# Conway's Game of Life - Project Documentation

## 1. Game Description

### Purpose and Rules of Game of Life

Conway's Game of Life is a cellular automaton devised by mathematician John Conway in 1970. It simulates a grid-based world where each cell follows simple birth, survival, and death rules to evolve into the next generation.

**Core Rules:**

1. **Survival**: Any live cell with 2 or 3 live neighbors survives to the next generation
2. **Birth**: Any dead cell with exactly 3 live neighbors becomes alive
3. **Death**: All other cells die or remain dead (underpopulation or overcrowding)

**Key Features:**

- **Periodic Boundary Conditions**: The grid wraps around at edges, simulating an infinite plane
- **Synchronous Updates**: All cells are updated simultaneously based on their current state
- **No Traditional Win/Lose**: It's a simulation, but we've added game-like objectives

## 2. Algorithm Explanation

### How Generations are Computed

The evolution algorithm follows these steps:

1. **Neighbor Counting**: For each cell, count live neighbors in 8 surrounding positions

   ```cpp
   int countLiveNeighbors(const vector<vector<bool>>& grid, int row, int col, int rows, int cols)
   ```

2. **State Determination**: Apply Conway's rules based on current state and neighbor count

   ```cpp
   if (grid[i][j]) {
       // Live cell: survives with 2-3 neighbors
       nextGrid[i][j] = (neighbors == 2 || neighbors == 3);
   } else {
       // Dead cell: becomes alive with exactly 3 neighbors
       nextGrid[i][j] = (neighbors == 3);
   }
   ```

3. **Synchronous Update**: All cells are updated simultaneously to avoid interference
4. **Boundary Handling**: Periodic boundary conditions using modulo arithmetic

### Mathematical Foundation

The algorithm implements a **cellular automaton** with:

- **State Space**: Binary (alive/dead)
- **Neighborhood**: Moore neighborhood (8 surrounding cells)
- **Transition Function**: Based on neighbor count and current state
- **Update Rule**: Synchronous (all cells updated at once)

## 3. Code Structure

### Main Components

**Core Functions:**

- `initializeGrid()`: Sets up the 2D grid structure
- `displayGrid()`: Visualizes the current state with ASCII characters
- `countLiveNeighbors()`: Implements neighbor counting with periodic boundaries
- `evolveGrid()`: Applies Conway's rules for one generation
- `runSimulation()`: Main simulation loop with game logic

**User Interface:**

- `showMenu()`: Main menu system
- `showGameModes()`: Game mode selection
- `manualSetup()`: Interactive cell placement
- `randomFill()`: Random grid generation

**File Operations:**

- `saveGrid()`: Saves current state to file
- `loadGrid()`: Loads state from file

**Game Logic:**

- `isStable()`: Detects stable configurations
- `countLiveCells()`: Counts total live cells
- Win condition checking for different game modes

### Data Structures

- **Primary Grid**: `vector<vector<bool>>` for current state
- **Next Generation Grid**: Separate grid for synchronous updates
- **Previous Grid**: For stability detection
- **Game Mode Enum**: Defines different win conditions

## 4. User Features

### Implemented Options

**Grid Initialization:**

- ✅ Random fill with configurable density
- ✅ Manual cell placement with coordinate input
- ✅ Customizable grid dimensions (up to 100x100)

**Simulation Control:**

- ✅ Step-by-step evolution
- ✅ Auto-run with configurable speed
- ✅ Pause/resume functionality
- ✅ Early exit option

**File Operations:**

- ✅ Save grid state to text file
- ✅ Load previously saved states
- ✅ Error handling for file operations

**Game Modes:**

1. **Stability Goal**: Win by reaching a stable configuration
2. **Survival Goal**: Keep cells alive for N generations
3. **Pattern Creation**: Create specific patterns (glider, etc.)
4. **Population Target**: Maintain population within range
5. **Time Attack**: Survive as long as possible

**Visualization:**

- ✅ ASCII-based grid display
- ✅ Generation counter
- ✅ Live cell counter
- ✅ Coordinate system for easy navigation

## 5. Sample Outputs

### Main Menu

```
=== Conway's Game of Life ===

=== Main Menu ===
1. Random fill grid
2. Manual setup
3. Run simulation
4. Save grid
5. Load grid
6. Exit
Enter your choice:
```

### Grid Display

```
=== Conway's Game of Life ===
Generation: 5 | Live Cells: 12

   0 1 2 3 4 5 6 7 8 9
 0 . . . . . . . . . .
 1 . . ■ . . . . . . .
 2 . . . ■ . . . . . .
 3 . ■ ■ ■ . . . . . .
 4 . . . . . . . . . .
 5 . . . . . . . . . .
```

### Game Mode Selection

```
=== Game Modes ===
1. Stability Goal - Reach a stable configuration
2. Survival Goal - Keep cells alive for N generations
3. Pattern Creation - Create specific patterns
4. Population Target - Maintain population in range
5. Time Attack - Survive as long as possible
Enter game mode:
```

## 6. Lessons Learned and Challenges

### Technical Challenges

1. **Synchronous Updates**: Ensuring all cells update simultaneously without interference
2. **Boundary Conditions**: Implementing periodic boundaries correctly
3. **Memory Management**: Efficient handling of multiple grid copies
4. **User Interface**: Creating an intuitive console-based interface

### Solutions Implemented

1. **Dual Grid System**: Separate current and next generation grids
2. **Modulo Arithmetic**: Simple periodic boundary implementation
3. **Vector Containers**: Automatic memory management
4. **Menu-Driven Interface**: Clear navigation and feedback

### Educational Value

- **Algorithm Design**: Understanding cellular automata principles
- **State Management**: Handling complex state transitions
- **User Experience**: Balancing functionality with usability
- **File I/O**: Persistent data storage and retrieval

## 7. Mathematical Background

### Cellular Automata Theory

Conway's Game of Life is a **2D cellular automaton** with:

- **States**: Binary (0 = dead, 1 = alive)
- **Neighborhood**: Moore neighborhood (8 cells)
- **Rules**: Totalistic (depends only on neighbor count)

### Emergent Behavior

The simple rules give rise to complex patterns:

- **Still Lifes**: Stable configurations (block, beehive, loaf)
- **Oscillators**: Repeating patterns (blinker, toad, beacon)
- **Spaceships**: Moving patterns (glider, lightweight spaceship)
- **Guns**: Patterns that produce other patterns

### Computational Complexity

- **Time Complexity**: O(n²) per generation for n×n grid
- **Space Complexity**: O(n²) for grid storage
- **Pattern Recognition**: NP-complete for general patterns

This implementation successfully demonstrates the fundamental principles of cellular automata while providing an engaging user experience with multiple game modes and objectives.
