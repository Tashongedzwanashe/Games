#!/bin/bash

# SFML Installation Script for Conway's Game of Life
# This script helps install SFML on different platforms

echo "=== SFML Installation Script ==="
echo "This script will help you install SFML for the Conway's Game of Life GUI"
echo ""

# Detect operating system
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    OS="windows"
else
    OS="unknown"
fi

echo "Detected OS: $OS"
echo ""

# Installation based on OS
case $OS in
    "linux")
        echo "Installing SFML on Linux..."
        
        # Check if apt is available (Ubuntu/Debian)
        if command -v apt-get &> /dev/null; then
            echo "Using apt package manager..."
            sudo apt-get update
            sudo apt-get install -y libsfml-dev
            echo "SFML installed successfully!"
        # Check if yum is available (RHEL/CentOS/Fedora)
        elif command -v yum &> /dev/null; then
            echo "Using yum package manager..."
            sudo yum install -y SFML-devel
            echo "SFML installed successfully!"
        # Check if pacman is available (Arch Linux)
        elif command -v pacman &> /dev/null; then
            echo "Using pacman package manager..."
            sudo pacman -S sfml
            echo "SFML installed successfully!"
        else
            echo "No supported package manager found."
            echo "Please install SFML manually:"
            echo "  Ubuntu/Debian: sudo apt-get install libsfml-dev"
            echo "  Fedora/RHEL: sudo yum install SFML-devel"
            echo "  Arch Linux: sudo pacman -S sfml"
        fi
        ;;
        
    "macos")
        echo "Installing SFML on macOS..."
        
        # Check if Homebrew is installed
        if command -v brew &> /dev/null; then
            echo "Using Homebrew package manager..."
            brew install sfml
            echo "SFML installed successfully!"
        else
            echo "Homebrew not found. Please install Homebrew first:"
            echo "  /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
            echo ""
            echo "Then run: brew install sfml"
        fi
        ;;
        
    "windows")
        echo "Installing SFML on Windows..."
        echo ""
        echo "For Windows, you have several options:"
        echo ""
        echo "1. Using vcpkg (recommended):"
        echo "   git clone https://github.com/Microsoft/vcpkg.git"
        echo "   cd vcpkg"
        echo "   ./bootstrap-vcpkg.bat"
        echo "   ./vcpkg install sfml"
        echo ""
        echo "2. Manual installation:"
        echo "   - Download SFML from https://www.sfml-dev.org/download.php"
        echo "   - Extract to C:/SFML"
        echo "   - Add C:/SFML/bin to your PATH"
        echo ""
        echo "3. Using MSYS2:"
        echo "   pacman -S mingw-w64-x86_64-sfml"
        echo ""
        echo "Please choose one of the above methods and follow the instructions."
        ;;
        
    *)
        echo "Unknown operating system: $OSTYPE"
        echo "Please install SFML manually for your system."
        echo "Visit: https://www.sfml-dev.org/download.php"
        ;;
esac

echo ""
echo "=== Installation Complete ==="
echo ""
echo "To test the installation, run:"
echo "  make check-sfml"
echo ""
echo "To compile and run the enhanced version:"
echo "  make"
echo "  make run"
echo ""
echo "If you encounter issues, you can still use the original version:"
echo "  make run-original" 