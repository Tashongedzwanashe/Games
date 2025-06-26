# Conway's Game of Life - OOP GUI Version

This is an object-oriented implementation of Conway's Game of Life with SFML graphics for manual setup and console-based simulation.

## Features

- **Object-Oriented Design** - Clean, modular code structure using classes
- **GUI Manual Setup** - SFML-based graphical interface for setting up initial grid
- **Console Simulation** - Console-based simulation with step-by-step or auto-run modes
- **Multiple game modes**:
  - Stability Goal - Reach a stable configuration
  - Survival Goal - Keep cells alive for N generations
  - Pattern Creation - Create specific patterns
  - Population Target - Maintain population in range (20-30)
  - Time Attack - Survive as long as possible
- **Random fill** - Generate random initial configurations
- **Save/Load** - Save and load grid configurations to/from files
- **Modern UI** - Beautiful graphical interface with gradients and styling

## Files

- `Game_of_life_OOP.cpp` - Main source code (OOP version with SFML)
- `Game_of_life_OOP.exe` - Compiled executable
- `README_GUI.md` - GUI-specific documentation
- `compile.bat` - Windows compilation script
- `Makefile` - Unix/Linux compilation makefile
- `install_sfml.bat` - Windows SFML installation script
- `install_sfml.sh` - Unix/Linux SFML installation script
- `arial.ttf` - Font file for GUI
- `sfml-*.dll` - SFML library files (Windows)

## Requirements

- **SFML 3.0** - Graphics library for GUI components
- **C++ compiler** - GCC, Clang, or MSVC
- **Windows**: Visual Studio or MinGW
- **Linux/Mac**: GCC or Clang

## Installation

### Windows

1. Run `install_sfml.bat` to install SFML dependencies
2. Or manually install SFML 3.0 and add to PATH

### Linux/Mac

1. Run `install_sfml.sh` to install SFML dependencies
2. Or use package manager: `sudo apt-get install libsfml-dev` (Ubuntu)

## Compilation

### Windows

```bash
compile.bat
```

### Linux/Mac

```bash
make
```

### Manual Compilation

```bash
g++ -o Game_of_life_OOP.exe Game_of_life_OOP.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

## How to Run

1. Navigate to this folder
2. Run `Game_of_life_OOP.exe`
3. Choose "Manual setup (GUI)" for graphical setup
4. Follow the on-screen instructions

## GUI Controls

- **Mouse click** - Toggle cells alive/dead
- **S key** - Save configuration
- **ESC key** - Cancel setup
- **Real-time cell count** - See live cell count as you set up

## Console Controls

- Use menu options (1-6) for main navigation
- Press Enter to step through generations
- Press 'a' for auto-run mode
- Press 'q' to quit simulation

## Architecture

The code is organized into several classes:

- `Grid` - Manages the game board state
- `ManualSetupWindow` - Handles GUI setup interface
- `GameEngine` - Controls simulation logic
- `GameDisplay` - Handles console visualization
- `GameController` - Main game loop and user interaction

## Differences from Console Version

- **OOP Design**: Cleaner, more maintainable code structure
- **GUI Setup**: Visual interface for initial configuration
- **SFML Integration**: Modern graphics library for GUI components
- **Enhanced UI**: Better visual feedback and styling
- **Modular Architecture**: Separated concerns into distinct classes
