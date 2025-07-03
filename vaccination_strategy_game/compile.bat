@echo off
echo Compiling Contain the Spread - Vaccination Strategy Game...
g++ -std=c++11 -Wall -Wextra -O2 -o contain_the_spread.exe contain_the_spread.cpp
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Run the game with: contain_the_spread.exe
) else (
    echo Compilation failed!
    pause
) 