# Memory Matching Game Documentation

## Game Description and Rules

### Overview

The Memory Matching Game is a console-based implementation of the classic card matching game where players need to find pairs of matching cards on a board where the cards are initially hidden.

### Rules

1. The game is played on a 4x4 grid containing 8 pairs of matching cards
2. All cards are initially hidden (displayed as '\*')
3. On each turn, the player:
   - Selects two cards by entering their row and column coordinates
   - The selected cards are revealed temporarily
   - If the cards match, they remain face up
   - If they don't match, they are hidden again after a brief pause
4. The game continues until all pairs are matched
5. The goal is to complete the game in the minimum number of moves possible

## Algorithm and Game Loop

### Core Algorithm

1. **Initialization Phase**

   ```cpp
   - Create a 4x4 board
   - Initialize pairs of letters (A-H)
   - Randomly shuffle the cards
   - Create a hidden board showing '*' for unrevealed cards
   ```

2. **Main Game Loop**

   ```cpp
   while (game not complete):
       - Display current board state
       - Get first card coordinates from player
       - Reveal first card
       - Get second card coordinates
       - Reveal second card
       - Check if cards match
           If match: Keep cards revealed
           If no match: Hide cards after delay
       - Increment move counter
   ```

3. **Win Condition**
   - Game completes when all pairs are matched
   - Display total number of moves used
   - Offer option to play again

## Program Structure

### Core Functions

1. `initializeBoard()`

   - Purpose: Sets up the game board with pairs of letters
   - Parameters: board, hiddenBoard, size
   - Returns: void

2. `shuffleBoard()`

   - Purpose: Randomly distributes cards on the board
   - Parameters: board, size
   - Returns: void

3. `displayBoard()`

   - Purpose: Shows current game state to player
   - Parameters: board, size
   - Returns: void

4. `makeMove()`

   - Purpose: Handles player's card selections and matching logic
   - Parameters: board, hiddenBoard, size
   - Returns: bool (true if move was completed)

5. `isGameComplete()`

   - Purpose: Checks if all pairs have been matched
   - Parameters: board, size
   - Returns: bool

6. `isValidMove()`
   - Purpose: Validates player's coordinate inputs
   - Parameters: row, col, size
   - Returns: bool

### Data Structures Used

- `vector<vector<char>>` for both the main board and hidden board
- Simple variables for tracking moves and game state

## Compilation and Running Instructions

### Prerequisites

- C++ compiler (g++ recommended)
- Basic command line knowledge

### Compilation Steps

1. Open terminal/command prompt
2. Navigate to the game directory
3. Compile using g++:
   ```bash
   g++ memory_matching_game.cpp -o memory_matching_game
   ```

### Running the Game

1. After compilation, run:

   ```bash
   ./memory_matching_game
   ```

   or on Windows:

   ```bash
   memory_matching_game.exe
   ```

2. Follow the on-screen prompts:
   - Enter coordinates as "row col" (e.g., "1 2")
   - Enter Y/N when asked to play again

### Sample Interaction

```
Welcome to the Memory Matching Game!

  0 1 2 3
0 * * * *
1 * * * *
2 * * * *
3 * * * *

Enter coordinates of first card (row col): 1 2
```

## Future Enhancements

Possible improvements that could be added:

1. Variable board sizes (2x2, 6x6)
2. Timer functionality
3. High score system
4. Colored console output
5. Different difficulty levels
