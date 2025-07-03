@echo off
REM Compile Set Game Extensions for Windows
REM Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924

echo ========================================
echo Set Game Extensions Compiler
echo ========================================

REM Check if g++ is available
g++ --version >nul 2>&1
if errorlevel 1 (
    echo Error: g++ compiler not found!
    echo Please install MinGW or another C++ compiler
    pause
    exit /b 1
)

echo Compiling AI Extension...
g++ -std=c++11 -o set_game_ai.exe set_game_ai.cpp
if errorlevel 1 (
    echo Error compiling AI extension!
    pause
    exit /b 1
)
echo AI Extension compiled successfully!

echo.
echo Compiling GUI Extension...
echo Note: This requires SFML libraries to be installed
g++ -std=c++11 -o set_game_gui.exe set_game_gui.cpp -lsfml-graphics -lsfml-window -lsfml-system
if errorlevel 1 (
    echo Warning: GUI extension compilation failed!
    echo This is likely due to missing SFML libraries
    echo To install SFML:
    echo 1. Download from https://www.sfml-dev.org/download.php
    echo 2. Extract to C:\SFML
    echo 3. Add C:\SFML\bin to your PATH
) else (
    echo GUI Extension compiled successfully!
)

echo.
echo Compiling Network Extension...
echo Note: This requires SFML libraries to be installed
g++ -std=c++11 -o set_game_network.exe set_game_network.cpp -lsfml-network -lsfml-system
if errorlevel 1 (
    echo Warning: Network extension compilation failed!
    echo This is likely due to missing SFML libraries
) else (
    echo Network Extension compiled successfully!
)

echo.
echo ========================================
echo Compilation Summary:
echo ========================================
if exist set_game_ai.exe (
    echo [OK] AI Extension: set_game_ai.exe
) else (
    echo [FAIL] AI Extension
)

if exist set_game_gui.exe (
    echo [OK] GUI Extension: set_game_gui.exe
) else (
    echo [FAIL] GUI Extension (requires SFML)
)

if exist set_game_network.exe (
    echo [OK] Network Extension: set_game_network.exe
) else (
    echo [FAIL] Network Extension (requires SFML)
)

echo.
echo To run the games:
echo   set_game_ai.exe
echo   set_game_gui.exe
echo   set_game_network.exe
echo.
pause 