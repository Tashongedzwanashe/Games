# Set Card Game - Two Player Terminal Version

A text-based implementation of the classic Set card game for two players, playable in the terminal.

## Game Rules

### What is a Set?

A Set consists of 3 cards where, for each of the 4 properties, the values are either:

- **All the same** (e.g., all red, all ovals, all solid, all 1's)
- **All different** (e.g., red, green, purple - all different colors)

### Card Properties

Each card has 4 properties, each with 3 possible values:

1. **Shape**: Oval, Squiggle, Diamond
2. **Color**: Red, Green, Purple
3. **Number**: 1, 2, or 3 symbols
4. **Shading**: Solid, Striped, Open

### Gameplay

- Two players take turns
- Each player has 30 seconds to find a valid Set
- If a Set is found: player earns 1 point, Set is removed, 3 new cards are dealt
- If no Set is found within 30 seconds: computer shows all possible Sets
- Game continues until no cards remain in deck and no Sets on board

## Compilation and Running

### Prerequisites

- C++ compiler with C++11 support (g++, clang++, or MSVC)
- Make (optional, for using Makefile)

### Compilation Options

#### Using Makefile (Recommended)

```bash
# Compile the game
make

# Or compile and run directly
make run

# Clean build files
make clean

# Show help
make help
```

#### Manual Compilation

```bash
# Using g++
g++ -std=c++11 -Wall -Wextra -O2 -o set_game set_game.cpp

# Using clang++
clang++ -std=c++11 -Wall -Wextra -O2 -o set_game set_game.cpp
```

### Running the Game

```bash
# On Unix-like systems
./set_game

# On Windows
set_game.exe
```

## How to Play

1. **Start the game**: Run the compiled executable
2. **Read the board**: Cards are displayed with indices [0], [1], [2], etc.
3. **Find a Set**: Look for 3 cards that form a valid Set
4. **Enter your choice**: Type 3 card indices separated by spaces (e.g., `1 4 7`)
5. **Wait for validation**: The game will check if your selection is a valid Set
6. **Continue**: Press Enter to continue to the next player's turn

### Example Game Session

```
=== Set Game ===
Player 1's Turn | Score: P1 - 0 | P2 - 0
Cards in deck: 69

Cards on table:
[0] 1 Red Solid Oval
[1] 2 Green Striped Diamond
[2] 3 Purple Open Squiggle
[3] 1 Green Solid Diamond
[4] 2 Red Striped Oval
[5] 3 Purple Open Diamond
[6] 1 Purple Solid Squiggle
[7] 2 Green Open Oval
[8] 3 Red Striped Squiggle
[9] 1 Red Open Diamond
[10] 2 Purple Solid Oval
[11] 3 Green Striped Squiggle

Enter 3 card numbers (e.g., 1 4 7): 0 4 8
Valid Set found! Cards: 1 Red Solid Oval, 2 Red Striped Oval, 3 Red Striped Squiggle
Player 1 earns 1 point!
Press Enter to continue...
```

## Features Implemented

✅ **Card Representation**: Struct with 4 properties (shape, color, number, shading)  
✅ **Deck Initialization**: All 81 unique cards (3⁴ combinations) with shuffling  
✅ **Game Board**: 12 cards displayed with indices  
✅ **Player Input**: Index-based card selection with validation  
✅ **Set Validation**: Complete logic for checking valid Sets  
✅ **Timeout System**: 30-second timer with computer assistance  
✅ **Computer Hints**: Shows all possible Sets when timeout occurs  
✅ **Scoring System**: Point tracking for both players  
✅ **Game End Condition**: Proper termination when no Sets remain  
✅ **Card Replacement**: Automatic dealing of new cards when Sets are found

## Technical Details

### Timeout Implementation

The game uses `chrono` library for precise timing and `thread` for non-blocking input checking. If no input is received within 30 seconds, the computer automatically finds and displays all possible Sets.

### Set Validation Algorithm

For each property (shape, color, number, shading), the algorithm checks if all three values are either:

- All identical (e.g., all red)
- All different (e.g., red, green, purple)

A valid Set must satisfy this condition for all four properties.

### Memory Management

- Uses STL containers (`vector`) for automatic memory management
- No manual memory allocation/deallocation required
- Efficient card removal and replacement using vector operations

## Troubleshooting

### Common Issues

**Compilation Errors:**

- Ensure your compiler supports C++11 (`-std=c++11` flag)
- Check that all required headers are available

**Runtime Issues:**

- On Windows, the timeout system may behave differently due to console input handling
- If input seems unresponsive, try pressing Enter to continue

**Game Logic Questions:**

- Remember: a Set requires ALL properties to be either all same OR all different
- Use the computer hints (timeout feature) to learn valid Set patterns

## License

This implementation is provided as educational software. The Set card game concept is a registered trademark of Set Enterprises, Inc.

## Contributing

Feel free to submit improvements, bug fixes, or feature requests. The code is structured to be easily extensible for additional features like:

- Single player mode
- Different difficulty levels
- Statistics tracking
- GUI version
