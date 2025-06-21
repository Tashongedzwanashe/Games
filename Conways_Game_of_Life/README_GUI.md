# Conway's Game of Life - Enhanced Version with GUI

This enhanced version of Conway's Game of Life includes a graphical user interface for manual setup, making it much easier to create custom patterns.

## New Features

### 🎯 Graphical Manual Setup

- **Clickable Grid**: Click any cell to toggle it between alive (black) and dead (white)
- **Real-time Feedback**: See live cell count update as you click
- **Easy Controls**:
  - Left-click to toggle cells
  - Press 'S' to save your layout
  - Press 'ESC' to cancel and return to terminal
- **Visual Grid**: Clear grid display with cell borders

### 🎮 Enhanced User Experience

- **Intuitive Interface**: No more typing coordinates manually
- **Immediate Visual Feedback**: See changes instantly
- **Error Prevention**: No invalid coordinate inputs
- **Faster Setup**: Create complex patterns quickly

## Requirements

### System Requirements

- C++17 compatible compiler (g++, clang++, MSVC)
- SFML 2.5+ library
- Operating System: Windows, macOS, or Linux

### SFML Installation

#### Windows

```bash
# Option 1: Using vcpkg (recommended)
vcpkg install sfml

# Option 2: Manual installation
# 1. Download SFML from https://www.sfml-dev.org/download.php
# 2. Extract to C:/SFML
# 3. Add C:/SFML/bin to your PATH
```

#### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### macOS

```bash
brew install sfml
```

## Quick Start

### 1. Install SFML

```bash
# Check your OS and run appropriate command
make install-sfml-ubuntu    # Ubuntu/Debian
make install-sfml-macos     # macOS
make install-sfml-windows   # Windows (vcpkg)
```

### 2. Compile and Run

```bash
# Compile the enhanced version
make

# Run the program
make run
```

### 3. Using the GUI Manual Setup

1. Start the program and enter grid dimensions
2. Select option 2: "Manual setup (Graphical)"
3. A window will open showing your grid
4. Click cells to toggle them alive/dead
5. Press 'S' to save your layout
6. Return to the main menu and run simulation

## How to Use the GUI

### Window Interface

- **Grid Display**: Shows your current grid with live cells in black
- **Instructions**: Displayed at the bottom of the window
- **Live Cell Counter**: Shows current number of live cells

### Controls

- **Left Mouse Click**: Toggle cell state (alive ↔ dead)
- **S Key**: Save current layout and return to terminal
- **ESC Key**: Cancel setup and return to terminal
- **Close Window**: Same as pressing ESC

### Tips for Creating Patterns

- **Glider**: Create a 3x3 pattern that moves diagonally
- **Blinker**: Create a 3-cell line that oscillates
- **Block**: Create a 2x2 square that remains stable
- **Toad**: Create a 4-cell pattern that oscillates

## File Structure

```
Conways_Game_of_Life/
├── Game_of_life_OOP.cpp    # Enhanced version with GUI
├── Game_of_life.cpp        # Original terminal-only version
├── Makefile                # Build automation
├── README_GUI.md          # This file
└── documentation.md       # Original documentation
```

## Troubleshooting

### Compilation Issues

#### SFML Not Found

```bash
# Check SFML installation
make check-sfml

# If not installed, install it:
make install-sfml-ubuntu    # Ubuntu/Debian
make install-sfml-macos     # macOS
make install-sfml-windows   # Windows
```

#### Font Issues

The program tries to load Arial font. If it fails:

- Windows: Should work automatically
- Linux: Install `fonts-liberation` package
- macOS: Should work automatically

### Runtime Issues

#### Window Doesn't Open

- Ensure SFML is properly installed
- Check that your system supports OpenGL
- Try running the original version: `make run-original`

#### Performance Issues

- Reduce grid size for better performance
- Close other applications to free up resources

## Comparison with Original Version

| Feature          | Original         | Enhanced            |
| ---------------- | ---------------- | ------------------- |
| Manual Setup     | Terminal input   | Graphical interface |
| Cell Toggle      | Type coordinates | Click cells         |
| Visual Feedback  | None             | Real-time display   |
| Error Prevention | Limited          | Full                |
| Setup Speed      | Slow             | Fast                |
| Dependencies     | None             | SFML required       |

## Advanced Usage

### Custom Grid Sizes

- Small grids (10x10): Good for testing patterns
- Medium grids (20x40): Balanced performance and space
- Large grids (50x100): For complex simulations

### Pattern Creation Tips

1. Start with simple patterns (blinker, block)
2. Experiment with different arrangements
3. Use the live cell counter to monitor population
4. Save interesting patterns for later use

### Performance Optimization

- Use smaller grids for faster simulation
- Close unnecessary applications
- Consider using the original version for very large grids

## Contributing

To extend this project:

1. Add more GUI features (pattern presets, zoom, etc.)
2. Implement real-time simulation in GUI
3. Add pattern recognition and analysis
4. Create pattern library with common configurations

## License

This project is provided as educational material. Feel free to modify and extend for your needs.

---

**Note**: The enhanced version requires SFML library. If you have issues with SFML, you can still use the original terminal version by running `make run-original`.
