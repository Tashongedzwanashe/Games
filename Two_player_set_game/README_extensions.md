# Set Game Extensions

## Authors

- Emmanuel Mufunde (100001936)
- George Kilibwa (100002924)

## Overview

This directory contains three optional extensions to the original Set Game implementation:

1. **AI Opponent Extension** (`set_game_ai.cpp`)
2. **GUI Extension** (`set_game_gui.cpp`)
3. **Network Multiplayer Extension** (`set_game_network.cpp`)

## 1. AI Opponent Extension

### Features

- Three difficulty levels: Easy, Medium, Hard
- Easy: Random card selection
- Medium: Finds valid sets when available, random otherwise
- Hard: Advanced strategy with set prioritization and future opportunity evaluation
- Configurable AI behavior and thinking time

### How to Compile

```bash
g++ -std=c++11 -o set_game_ai set_game_ai.cpp
```

### How to Run

```bash
./set_game_ai
```

### Game Modes

1. Human vs Human
2. Human vs AI (Easy)
3. Human vs AI (Medium)
4. Human vs AI (Hard)

### AI Strategy Details

- **Easy**: Completely random selection of 3 cards
- **Medium**: Searches for valid sets and picks one randomly if found
- **Hard**: Evaluates all possible sets and chooses the one that creates the most opportunities for future sets

## 2. GUI Extension

### Features

- Graphical user interface using SFML
- Visual card representation with shapes, colors, numbers, and shading
- Mouse-based card selection
- Real-time game status display
- Keyboard shortcuts for hints and game control
- Smooth animations and visual feedback

### Dependencies

- SFML 2.5+ (Graphics, Window, System modules)

### How to Install SFML

#### Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### Windows:

1. Download SFML from https://www.sfml-dev.org/download.php
2. Extract to `C:\SFML`
3. Add `C:\SFML\bin` to your PATH

#### macOS:

```bash
brew install sfml
```

### How to Compile

```bash
g++ -std=c++11 -o set_game_gui set_game_gui.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### How to Run

```bash
./set_game_gui
```

### Controls

- **Mouse**: Click cards to select/deselect
- **H**: Show hint (number of possible sets)
- **A**: Add 3 more cards (when no sets are available)
- **R**: Reset game

### Visual Features

- Cards display with proper shapes (Oval, Squiggle, Diamond)
- Color coding (Red, Green, Purple)
- Shading representation (Solid, Striped, Open)
- Number of symbols (1, 2, or 3)
- Selected cards highlighted in yellow
- Real-time score and turn display

## 3. Network Multiplayer Extension

### Features

- Client-server architecture
- Real-time game synchronization
- Network state management
- Automatic turn-based gameplay
- Connection status monitoring

### Dependencies

- SFML 2.5+ (Network module)

### How to Compile

```bash
g++ -std=c++11 -o set_game_network set_game_network.cpp -lsfml-network -lsfml-system
```

### How to Run

#### Start Server:

```bash
./set_game_network
# Choose option 1 (Start Server)
# Enter port number (e.g., 12345)
```

#### Connect to Server:

```bash
./set_game_network
# Choose option 2 (Connect to Server)
# Enter server address (e.g., 127.0.0.1)
# Enter port number (e.g., 12345)
```

### Network Protocol

- TCP-based communication
- Game state synchronization
- Player move transmission
- Automatic turn management

### Network Features

- Real-time game state updates
- Automatic player turn detection
- Connection status monitoring
- Error handling for network issues

## Building All Extensions

### Using the Makefile

```bash
# Build all extensions
make all

# Build specific extension
make set_game_ai
make set_game_gui
make set_game_network

# Clean build files
make clean

# Install SFML (Ubuntu/Debian)
make install_sfml_ubuntu

# Run tests
make test
```

### Manual Compilation

```bash
# AI Extension
g++ -std=c++11 -o set_game_ai set_game_ai.cpp

# GUI Extension
g++ -std=c++11 -o set_game_gui set_game_gui.cpp -lsfml-graphics -lsfml-window -lsfml-system

# Network Extension
g++ -std=c++11 -o set_game_network set_game_network.cpp -lsfml-network -lsfml-system
```

## File Structure

```
Two_player_set_game/
├── set_game.cpp              # Original game
├── set_game_ai.cpp           # AI extension
├── set_game_gui.cpp          # GUI extension
├── set_game_network.cpp      # Network extension
├── Makefile_extensions       # Build configuration
├── README_extensions.md      # This file
└── arial.ttf                # Font file for GUI
```

## Game Rules (Set Game)

A Set consists of 3 cards where each property is either:

- **All the same** (e.g., all red, all ovals, all solid, all 1s)
- **All different** (e.g., red, green, purple; oval, squiggle, diamond)

### Card Properties

- **Shape**: Oval, Squiggle, Diamond
- **Color**: Red, Green, Purple
- **Number**: 1, 2, 3 symbols
- **Shading**: Solid, Striped, Open

## Troubleshooting

### Common Issues

#### SFML Not Found

```bash
# Ubuntu/Debian
sudo apt-get install libsfml-dev

# Check if SFML is installed
pkg-config --modversion sfml-all
```

#### Compilation Errors

- Ensure you have a C++11 compatible compiler
- Check that SFML libraries are properly linked
- Verify font file (arial.ttf) is in the same directory for GUI

#### Network Connection Issues

- Check firewall settings
- Ensure port is not already in use
- Verify server address and port number
- Test with localhost (127.0.0.1) first

### Performance Tips

- GUI version runs at 60 FPS by default
- Network version includes connection timeout handling
- AI version has configurable thinking time

## Future Enhancements

- Web-based multiplayer using WebSockets
- Mobile app version
- Tournament mode with multiple players
- Advanced AI with machine learning
- Custom card themes and skins
- Statistics and leaderboards

## License

This project is part of a university assignment. Please respect academic integrity guidelines.
