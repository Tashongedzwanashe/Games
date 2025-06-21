@echo off
echo Compiling Conway's Game of Life with SFML...
g++ -std=c++17 -O2 -Wall -Wextra -I"C:/SFML/SFML-3.0.0/include" -o Game_of_life_OOP Game_of_life_OOP.cpp -L"C:/SFML/SFML-3.0.0/lib" -lsfml-graphics -lsfml-window -lsfml-system
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo You can now run: Game_of_life_OOP.exe
) else (
    echo Compilation failed!
)
pause 