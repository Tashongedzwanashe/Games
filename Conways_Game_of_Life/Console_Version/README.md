# Conway's Game of Life - Console Version

This is the traditional console-based implementation of Conway's Game of Life with automatic win condition detection.

## Features

- **Console-based interface** - Runs entirely in the command line
- **Auto-detect win conditions** - Automatically detects when you achieve various win conditions
- **Multiple game modes**:
  - Stability Goal - Reach a stable configuration
  - Survival Goal - Keep cells alive for N generations
  - Pattern Creation - Create specific patterns (glider, blinker, block)
  - Population Target - Maintain population in range (20-30)
  - Time Attack - Survive as long as possible
- **Manual setup** - Set up initial grid manually through console input
- **Random fill** - Generate random initial configurations
- **Save/Load** - Save and load grid configurations to/from files
- **Real-time statistics** - Track generation count, live cells, and win conditions

## Files

- `Game_of_life.cpp` - Main source code (console version)
- `Game_of_life.exe` - Compiled executable
- `documentation.md` - Detailed documentation

## How to Run

1. Navigate to this folder
2. Run `Game_of_life.exe`
3. Follow the on-screen instructions

## Compilation

To compile from source:

```bash
g++ -o Game_of_life.exe Game_of_life.cpp
```

## Game Controls

- Use menu options (1-6) for main navigation
- Enter coordinates for manual setup
- Press Enter to step through generations
- Press 'a' for auto-run mode
- Press 'q' to quit simulation

## Win Conditions

The game automatically detects:

- Stability (no changes for 2+ generations)
- Survival milestones (10, 25, 50, 100 generations)
- Population balance (20-30 cells for 20+ generations)
- Pattern creation (glider, blinker, block patterns)
- Time attack achievements (100+, 500+ generations)
