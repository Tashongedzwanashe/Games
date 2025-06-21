@echo off
REM SFML Installation Script for Conway's Game of Life (Windows)
REM This script helps install SFML on Windows

echo === SFML Installation Script for Windows ===
echo This script will help you install SFML for the Conway's Game of Life GUI
echo.

echo Detected OS: Windows
echo.

echo For Windows, you have several installation options:
echo.

echo 1. Using vcpkg (recommended):
echo    git clone https://github.com/Microsoft/vcpkg.git
echo    cd vcpkg
echo    bootstrap-vcpkg.bat
echo    vcpkg install sfml
echo.

echo 2. Manual installation:
echo    - Download SFML from https://www.sfml-dev.org/download.php
echo    - Extract to C:\SFML
echo    - Add C:\SFML\bin to your PATH
echo.

echo 3. Using MSYS2:
echo    pacman -S mingw-w64-x86_64-sfml
echo.

echo 4. Using Chocolatey (if installed):
echo    choco install sfml
echo.

echo Please choose one of the above methods and follow the instructions.
echo.

echo === Quick Installation Guide ===
echo.

echo Option 1 - vcpkg (automatic):
echo 1. Open Command Prompt as Administrator
echo 2. Run: git clone https://github.com/Microsoft/vcpkg.git
echo 3. Run: cd vcpkg
echo 4. Run: bootstrap-vcpkg.bat
echo 5. Run: vcpkg install sfml
echo 6. Run: vcpkg integrate install
echo.

echo Option 2 - Manual (step by step):
echo 1. Visit https://www.sfml-dev.org/download.php
echo 2. Download SFML for your compiler (Visual Studio, MinGW, etc.)
echo 3. Extract to C:\SFML
echo 4. Add C:\SFML\bin to your system PATH
echo 5. Copy DLL files to your project directory or system PATH
echo.

echo === Testing Installation ===
echo.
echo After installation, test with:
echo   make check-sfml
echo.
echo To compile and run the enhanced version:
echo   make
echo   make run
echo.
echo If you encounter issues, you can still use the original version:
echo   make run-original
echo.

pause 