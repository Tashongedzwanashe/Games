# Minesweeper Console Game

## 🎮 Game Overview

Minesweeper is a classic single-player puzzle game where the objective is to clear a rectangular board containing hidden "mines" or bombs without detonating any of them. The game is won when all non-mine cells are revealed.

### Game Rules

- **Board**: 2D grid (8×8, 10×10, 12×12, or custom size)
- **Mines**: Randomly placed hidden mines on the board
- **Revealing Cells**:
  - Click a cell to reveal it
  - If it's a mine: Game Over 💥
  - If it's safe: Shows number of adjacent mines
  - If 0 adjacent mines: Automatically reveals neighboring cells
- **Flagging**: Mark suspected mine locations with flags
- **Win Condition**: Reveal all non-mine cells ✅
- **Lose Condition**: Reveal a mine 💥

## 🚀 How to Run

### Prerequisites

- C++ compiler (g++ recommended)
- Windows, Linux, or macOS

### Compilation

**Windows:**

```bash
# Option 1: Use batch file
compile.bat

# Option 2: Manual compilation
g++ -std=c++11 -Wall -Wextra -O2 -o minesweeper.exe minesweeper.cpp
```

**Linux/macOS:**

```bash
# Option 1: Use Makefile
make

# Option 2: Manual compilation
g++ -std=c++11 -Wall -Wextra -O2 -o minesweeper minesweeper.cpp
```

### Running the Game

```bash
# Windows
minesweeper.exe

# Linux/macOS
./minesweeper
```

## 🎯 How to Play

1. **Choose Difficulty**: Select from Easy, Medium, Hard, or Custom
2. **Game Commands**:
   - `row column` - Reveal cell at specified position
   - `F row column` - Flag/unflag cell at specified position
   - `quit` - Exit game

### Example Commands

```
Enter command: 3 4      # Reveal cell at row 3, column 4
Enter command: F 2 5    # Flag cell at row 2, column 5
Enter command: quit     # Exit game
```

## 📊 Board Display

- `.` - Hidden cell
- `F` - Flagged cell
- ` ` (space) - Revealed empty cell (0 adjacent mines)
- `1-8` - Number of adjacent mines
- `*` - Mine (shown after game ends)

### Sample Board Output

```
   0  1  2  3  4  5  6  7
0  .  .  .  .  .  .  .  .
1  .  .  .  .  .  .  .  .
2  .  .  .  .  .  .  .  .
3  .  .  .  .  .  .  .  .
4  .  .  .  .  .  .  .  .
5  .  .  .  .  .  .  .  .
6  .  .  .  .  .  .  .  .
7  .  .  .  .  .  .  .  .
```

## 🏗️ Code Structure

### Main Components

1. **Cell Structure** (`struct Cell`)

   - `isMine`: Boolean indicating if cell contains a mine
   - `isRevealed`: Boolean indicating if cell has been revealed
   - `isFlagged`: Boolean indicating if cell is flagged
   - `adjacentMines`: Integer count of adjacent mines

2. **Minesweeper Class**
   - **Constructor**: Initializes board, places mines, calculates adjacent counts
   - **placeMines()**: Randomly distributes mines across the board
   - **calculateAdjacentMines()**: Computes mine counts for all cells
   - **revealCell()**: Handles cell revelation and recursive neighbor revealing
   - **flagCell()**: Toggles flag state of cells
   - **printBoard()**: Displays current game state
   - **play()**: Main game loop

### Key Functions

- `countAdjacentMines(int r, int c)`: Counts mines in 8 surrounding cells
- `checkWinCondition()`: Verifies if all non-mine cells are revealed
- `printFinalBoard()`: Shows complete board after game ends

## 🎮 Sample Game Session

```
Welcome to Minesweeper!
Choose board size:
1. Easy (8x8, 10 mines)
2. Medium (10x10, 15 mines)
3. Hard (12x12, 20 mines)
4. Custom
Enter choice (1-4): 1

=== MINESWEEPER ===
Commands:
  r c     - Reveal cell at row r, column c
  F r c   - Flag/unflag cell at row r, column c
  quit    - Exit game
Mines: 10

   0  1  2  3  4  5  6  7
0  .  .  .  .  .  .  .  .
1  .  .  .  .  .  .  .  .
2  .  .  .  .  .  .  .  .
3  .  .  .  .  .  .  .  .
4  .  .  .  .  .  .  .  .
5  .  .  .  .  .  .  .  .
6  .  .  .  .  .  .  .  .
7  .  .  .  .  .  .  .  .

Enter command: 3 4

   0  1  2  3  4  5  6  7
0  .  .  .  .  .  .  .  .
1  .  .  .  .  .  .  .  .
2  .  .  .  .  .  .  .  .
3  .  .  .  .  .  .  .  1  .
4  .  .  .  .  .  .  .  .
5  .  .  .  .  .  .  .  .
6  .  .  .  .  .  .  .  .
7  .  .  .  .  .  .  .  .

Enter command: F 2 3

   0  1  2  3  4  5  6  7
0  .  .  .  .  .  .  .  .
1  .  .  .  .  .  .  .  .
2  .  .  .  F  .  .  .  .
3  .  .  .  .  .  .  .  1  .
4  .  .  .  .  .  .  .  .
5  .  .  .  .  .  .  .  .
6  .  .  .  .  .  .  .  .
7  .  .  .  .  .  .  .  .
```

## 🔧 Technical Details

### Algorithm Complexity

- **Time Complexity**: O(rows × cols) for board initialization
- **Space Complexity**: O(rows × cols) for board storage
- **Recursive Reveal**: O(rows × cols) worst case for flood fill

### Random Number Generation

- Uses `srand(time(0))` for mine placement
- Ensures different game layouts on each run

### Input Validation

- Bounds checking for all cell operations
- Command parsing with error handling
- Graceful handling of invalid inputs

## 🎯 Game Features

### Difficulty Levels

- **Easy**: 8×8 grid, 10 mines
- **Medium**: 10×10 grid, 15 mines
- **Hard**: 12×12 grid, 20 mines
- **Custom**: User-defined size and mine count

### Game Mechanics

- ✅ Random mine placement
- ✅ Adjacent mine counting
- ✅ Recursive cell revealing
- ✅ Flag/unflag functionality
- ✅ Win/lose condition checking
- ✅ Complete board display on game end

## 🚀 Future Improvements

1. **Enhanced UI**: Color coding, better formatting
2. **Timer**: Track game duration
3. **High Scores**: Save best times
4. **Undo Feature**: Allow move reversal
5. **Hint System**: Provide strategic suggestions
6. **Multiple Boards**: Save/load game states
7. **Sound Effects**: Audio feedback
8. **GUI Version**: Graphical interface

## 📝 Reflection

### What I Learned

- **Object-Oriented Design**: Structured code with classes and methods
- **Recursive Algorithms**: Flood fill for revealing empty areas
- **Input Parsing**: Robust command-line interface
- **Game State Management**: Tracking win/lose conditions
- **Random Number Generation**: Proper seeding and distribution

### Challenges Faced

- **Recursive Logic**: Ensuring proper neighbor revelation without infinite loops
- **Input Validation**: Handling various user input formats
- **Board Display**: Creating readable console output
- **Edge Cases**: Managing boundary conditions and invalid moves

### Code Quality

- **Modular Design**: Separated concerns into distinct functions
- **Error Handling**: Graceful handling of invalid inputs
- **Documentation**: Comprehensive comments and README
- **Cross-Platform**: Works on Windows, Linux, and macOS

This project demonstrates fundamental programming concepts including data structures, algorithms, user interaction, and game development principles.
