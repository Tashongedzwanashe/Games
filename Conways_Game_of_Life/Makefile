# Makefile for Conway's Game of Life (OOP Version with GUI)

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# SFML library flags (adjust paths as needed for your system)
SFML_DIR = /usr/local
SFML_INCLUDE = -I$(SFML_DIR)/include
SFML_LIBS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

# For Windows with SFML installed in standard location
ifeq ($(OS),Windows_NT)
    SFML_INCLUDE = -I"C:/SFML/include"
    SFML_LIBS = -L"C:/SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system
endif

# Target executables
TARGET_OOP = Game_of_life_OOP
TARGET_ORIGINAL = Game_of_life

# Source files
SOURCES_OOP = Game_of_life_OOP.cpp
SOURCES_ORIGINAL = Game_of_life.cpp

# Default target
all: $(TARGET_OOP)

# Compile the OOP version with GUI
$(TARGET_OOP): $(SOURCES_OOP)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -o $(TARGET_OOP) $(SOURCES_OOP) $(SFML_LIBS)

# Compile the original version (no GUI)
$(TARGET_ORIGINAL): $(SOURCES_ORIGINAL)
	$(CXX) $(CXXFLAGS) -o $(TARGET_ORIGINAL) $(SOURCES_ORIGINAL)

# Run the OOP version
run: $(TARGET_OOP)
	./$(TARGET_OOP)

# Run the original version
run-original: $(TARGET_ORIGINAL)
	./$(TARGET_ORIGINAL)

# Install SFML (Ubuntu/Debian)
install-sfml-ubuntu:
	sudo apt-get update
	sudo apt-get install libsfml-dev

# Install SFML (macOS with Homebrew)
install-sfml-macos:
	brew install sfml

# Install SFML (Windows with vcpkg)
install-sfml-windows:
	vcpkg install sfml

# Download SFML for Windows (manual installation)
download-sfml-windows:
	@echo "Downloading SFML for Windows..."
	@echo "Please visit: https://www.sfml-dev.org/download.php"
	@echo "Download the appropriate version for your compiler"
	@echo "Extract to C:/SFML and ensure the DLLs are in your PATH"

# Check SFML installation
check-sfml:
	@echo "Checking SFML installation..."
	@echo "SFML_INCLUDE: $(SFML_INCLUDE)"
	@echo "SFML_LIBS: $(SFML_LIBS)"
	@echo "If compilation fails, you may need to install SFML:"
	@echo "  Ubuntu/Debian: make install-sfml-ubuntu"
	@echo "  macOS: make install-sfml-macos"
	@echo "  Windows: make install-sfml-windows or make download-sfml-windows"

# Clean build files
clean:
	rm -f $(TARGET_OOP) $(TARGET_ORIGINAL) *.o

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Compile the OOP version with GUI"
	@echo "  run              - Compile and run the OOP version"
	@echo "  run-original     - Compile and run the original version"
	@echo "  install-sfml-ubuntu  - Install SFML on Ubuntu/Debian"
	@echo "  install-sfml-macos   - Install SFML on macOS"
	@echo "  install-sfml-windows - Install SFML on Windows (vcpkg)"
	@echo "  download-sfml-windows - Download SFML for Windows"
	@echo "  check-sfml       - Check SFML installation"
	@echo "  clean            - Remove build files"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Note: The OOP version requires SFML library for the GUI."

.PHONY: all run run-original install-sfml-ubuntu install-sfml-macos install-sfml-windows download-sfml-windows check-sfml clean help 