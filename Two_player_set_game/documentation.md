# Set Game Implementation Documentation

## Overview

This document provides technical details about the implementation of the Set card game, including algorithms, data structures, and design decisions.

## Architecture

### Core Classes and Structures

#### Card Struct

```cpp
struct Card {
    int shape;    // 0: Oval, 1: Squiggle, 2: Diamond
    int color;    // 0: Red, 1: Green, 2: Purple
    int number;   // 0: 1, 1: 2, 2: 3
    int shading;  // 0: Solid, 1: Striped, 2: Open
};
```

**Design Decision**: Using integers (0-2) instead of enums for simplicity and memory efficiency. String representations are handled separately for display purposes.

#### SetGame Class

The main game controller class that manages:

- Deck initialization and shuffling
- Board state management
- Player turn handling
- Set validation
- Scoring system

## Key Algorithms

### 1. Deck Initialization

**Algorithm**: Generate all 81 unique cards using nested loops

```cpp
for (int shape = 0; shape < 3; shape++) {
    for (int color = 0; color < 3; color++) {
        for (int number = 0; number < 3; number++) {
            for (int shading = 0; shading < 3; shading++) {
                deck.emplace_back(shape, color, number, shading);
            }
        }
    }
}
```

**Time Complexity**: O(1) - fixed 81 cards
**Space Complexity**: O(1) - fixed 81 cards

### 2. Set Validation Algorithm

**Core Logic**: For each property, check if all three values are either all identical or all different.

```cpp
bool isValidSet(const Card& card1, const Card& card2, const Card& card3) {
    bool shapeValid = (card1.shape == card2.shape && card2.shape == card3.shape) ||
                     (card1.shape != card2.shape && card2.shape != card3.shape && card1.shape != card3.shape);
    // Repeat for color, number, shading
    return shapeValid && colorValid && numberValid && shadingValid;
}
```

**Time Complexity**: O(1) - constant time for 4 property checks
**Correctness**: This algorithm correctly identifies valid Sets according to the official Set game rules.

### 3. Find All Sets Algorithm

**Algorithm**: Brute force approach checking all possible 3-card combinations

```cpp
for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = i + 1; j < board.size(); j++) {
        for (size_t k = j + 1; k < board.size(); k++) {
            if (isValidSet(board[i], board[j], board[k])) {
                sets.push_back({i, j, k});
            }
        }
    }
}
```

**Time Complexity**: O(n³) where n is the number of cards on the board
**Space Complexity**: O(n³) in worst case (when many sets exist)
**Optimization**: Could be improved with more sophisticated algorithms, but current approach is sufficient for typical board sizes (12-15 cards).

### 4. Timeout Implementation

**Approach**: Non-blocking input with timer

```cpp
auto start = chrono::steady_clock::now();
while (chrono::steady_clock::now() - start < chrono::seconds(TIMEOUT_SECONDS)) {
    if (cin.rdbuf()->in_avail()) {
        getline(cin, input);
        break;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}
```

**Design Decision**: Using polling approach instead of async I/O for simplicity and cross-platform compatibility.

## Data Structures

### 1. Deck Management

- **Container**: `std::vector<Card>`
- **Operations**: `push_back()`, `pop_back()`, `shuffle()`
- **Rationale**: Vector provides efficient random access and dynamic sizing

### 2. Board Management

- **Container**: `std::vector<Card>`
- **Operations**: `push_back()`, `erase()`, random access
- **Rationale**: Vector allows efficient card removal and addition

### 3. Set Storage

- **Container**: `std::vector<std::vector<int>>`
- **Structure**: Each inner vector contains 3 indices representing a Set
- **Rationale**: Simple and efficient for storing multiple Sets

## Memory Management

### Automatic Memory Management

- Uses STL containers exclusively
- No manual memory allocation/deallocation
- RAII principles ensure proper cleanup

### Memory Efficiency

- Card struct: 16 bytes (4 ints × 4 bytes)
- Total deck memory: ~1.3 KB (81 cards × 16 bytes)
- Board memory: ~200 bytes (12-15 cards × 16 bytes)

## Error Handling

### Input Validation

1. **Card Count**: Ensures exactly 3 cards selected
2. **Index Range**: Validates indices are within board bounds
3. **Duplicate Check**: Prevents selecting the same card multiple times
4. **Set Validation**: Verifies selected cards form a valid Set

### Robustness Features

- Graceful handling of invalid input
- Timeout protection against infinite waits
- Automatic game state recovery after errors

## Performance Characteristics

### Time Complexity Analysis

- **Game Initialization**: O(1) - fixed deck size
- **Set Validation**: O(1) - constant time per validation
- **Find All Sets**: O(n³) - where n is board size
- **Card Removal/Addition**: O(n) - vector operations
- **Overall Game**: O(m × n³) - where m is number of turns

### Space Complexity Analysis

- **Deck**: O(1) - fixed 81 cards
- **Board**: O(n) - where n is current board size
- **Set Storage**: O(n³) - worst case for all possible sets
- **Total**: O(n³) - dominated by set storage

## Cross-Platform Considerations

### Compiler Compatibility

- Uses C++11 standard features
- Compatible with g++, clang++, MSVC
- No platform-specific code

### Input Handling

- Uses standard C++ I/O streams
- Timeout implementation works on Windows and Unix-like systems
- May behave differently on different terminals

## Testing Strategy

### Unit Tests

- Set validation logic tested with known valid/invalid combinations
- Edge cases covered (all same, all different, mixed properties)
- Comprehensive combination testing

### Integration Tests

- Full game flow testing
- Timeout mechanism verification
- Score tracking validation

## Future Enhancements

### Potential Improvements

1. **Algorithm Optimization**: More efficient Set finding algorithms
2. **GUI Version**: Graphical interface using SFML or similar
3. **Network Play**: Multiplayer over network
4. **AI Opponents**: Computer players with different difficulty levels
5. **Statistics Tracking**: Game history and performance metrics
6. **Custom Rules**: Variant game modes

### Scalability Considerations

- Current implementation handles typical game sizes efficiently
- For larger boards, Set finding algorithm could be optimized
- Memory usage is minimal and scales well

## Conclusion

The implementation provides a complete, robust, and efficient Set game with all required features. The code is well-structured, thoroughly tested, and ready for production use. The modular design allows for easy extension and modification.
