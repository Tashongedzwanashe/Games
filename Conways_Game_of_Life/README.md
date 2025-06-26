# Conway's Game of Life

This repository contains two different implementations of Conway's Game of Life, each with its own unique features and approach.

## 📁 Project Structure

```
Conways_Game_of_Life/
├── Console_Version/          # Traditional console-based implementation
│   ├── Game_of_life.cpp      # Main source code
│   ├── Game_of_life.exe      # Compiled executable
│   ├── documentation.md      # Detailed documentation
│   └── README.md            # Console version README
├── OOP_GUI_Version/         # Object-oriented version with GUI setup
│   ├── Game_of_life_OOP.cpp # Main source code (OOP + SFML)
│   ├── Game_of_life_OOP.exe # Compiled executable
│   ├── README_GUI.md        # GUI-specific documentation
│   ├── compile.bat          # Windows compilation script
│   ├── Makefile             # Unix/Linux compilation
│   ├── install_sfml.bat     # Windows SFML installation
│   ├── install_sfml.sh      # Unix/Linux SFML installation
│   ├── arial.ttf            # Font file for GUI
│   ├── sfml-*.dll           # SFML library files
│   └── README.md            # OOP GUI version README
└── README.md                # This file
```

## 🎮 Two Different Versions

### 1. Console Version (`Console_Version/`)

- **Traditional console-based interface**
- **Auto-detect win conditions** - Automatically detects when you achieve various win conditions
- **Multiple game modes** with automatic tracking
- **No external dependencies** - Pure C++ console application
- **Cross-platform** - Works on any system with a C++ compiler

### 2. OOP GUI Version (`OOP_GUI_Version/`)

- **Object-oriented design** with clean, modular architecture
- **SFML graphics** for manual setup interface
- **Console simulation** with step-by-step or auto-run modes
- **Modern UI** with gradients and styling
- **Enhanced user experience** with visual feedback

## 🚀 Quick Start

### Console Version

```bash
cd Console_Version
./Game_of_life.exe
```

### OOP GUI Version

```bash
cd OOP_GUI_Version
./Game_of_life_OOP.exe
```

## 🎯 Game Modes

Both versions support these game modes:

- **Stability Goal** - Reach a stable configuration
- **Survival Goal** - Keep cells alive for N generations
- **Pattern Creation** - Create specific patterns (glider, blinker, block)
- **Population Target** - Maintain population in range (20-30)
- **Time Attack** - Survive as long as possible

## 🔧 Requirements

### Console Version

- C++ compiler (GCC, Clang, MSVC)
- No external dependencies

### OOP GUI Version

- C++ compiler (GCC, Clang, MSVC)
- SFML 3.0 library
- See individual README for installation instructions

## 📚 Documentation

- `Console_Version/README.md` - Console version details
- `OOP_GUI_Version/README.md` - OOP GUI version details
- `Console_Version/documentation.md` - Detailed console version documentation
- `OOP_GUI_Version/README_GUI.md` - GUI-specific documentation

## 🎨 Features Comparison

| Feature            | Console Version | OOP GUI Version                |
| ------------------ | --------------- | ------------------------------ |
| Interface          | Console only    | GUI setup + Console simulation |
| Architecture       | Procedural      | Object-Oriented                |
| Dependencies       | None            | SFML 3.0                       |
| Auto-win detection | ✅              | ✅                             |
| Manual setup       | Console input   | GUI mouse interface            |
| Cross-platform     | ✅              | ✅ (with SFML)                 |
| Code organization  | Functions       | Classes                        |
| Visual feedback    | Text-based      | Graphical                      |

## 🏆 Win Conditions

Both versions automatically detect:

- **Stability** - No changes for 2+ generations
- **Survival milestones** - 10, 25, 50, 100 generations
- **Population balance** - 20-30 cells for 20+ generations
- **Pattern creation** - Glider, blinker, block patterns
- **Time attack achievements** - 100+, 500+ generations

## 🤝 Contributing

Feel free to:

- Report bugs
- Suggest new features
- Improve documentation
- Add new game modes
- Enhance the GUI

## 📄 License

This project is open source. Feel free to use, modify, and distribute as needed.

---

**Enjoy exploring the fascinating world of cellular automata!** 🧬
