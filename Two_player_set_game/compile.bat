@echo off
echo Compiling Set Game...

REM Try to find g++ compiler
where g++ >nul 2>&1
if %errorlevel% == 0 (
    echo Using g++ compiler...
    g++ -std=c++11 -Wall -Wextra -O2 -o set_game.exe set_game.cpp
    if %errorlevel% == 0 (
        echo Compilation successful!
        echo Run the game with: set_game.exe
    ) else (
        echo Compilation failed with g++
    )
) else (
    echo g++ not found, trying clang++...
    where clang++ >nul 2>&1
    if %errorlevel% == 0 (
        echo Using clang++ compiler...
        clang++ -std=c++11 -Wall -Wextra -O2 -o set_game.exe set_game.cpp
        if %errorlevel% == 0 (
            echo Compilation successful!
            echo Run the game with: set_game.exe
        ) else (
            echo Compilation failed with clang++
        )
    ) else (
        echo Neither g++ nor clang++ found.
        echo Please install a C++ compiler with C++11 support.
        echo Recommended: MinGW-w64, MSYS2, or Visual Studio Build Tools
    )
)

pause 