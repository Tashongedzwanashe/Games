@echo off
echo Compiling Forest Fire Simulation...

REM Check if g++ is available
g++ --version >nul 2>&1
if errorlevel 1 (
    echo Error: g++ compiler not found!
    echo Please install MinGW or another C++ compiler.
    pause
    exit /b 1
)

REM Compile the program
g++ -std=c++11 -Wall -Wextra -O2 forest_fire.cpp -o forest_fire.exe

if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Compilation successful!
echo.
echo To run the simulation, type: forest_fire.exe
echo.
pause 