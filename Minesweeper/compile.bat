@echo off
echo Compiling Minesweeper...
g++ -std=c++11 -Wall -Wextra -O2 -o minesweeper.exe minesweeper.cpp
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Run the game with: minesweeper.exe
) else (
    echo Compilation failed!
    pause
) 