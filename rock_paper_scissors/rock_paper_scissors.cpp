// Rock, Paper, Scissors Game
// Author: Mufunde Emmanuel - 100001936 and George Kilibwa - 100002924
// Date: 2025-06-17
//Submission time: 12:35 PM AM

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// Function prototypes
int getUserChoice();
int getComputerChoice();
string convertChoiceToString(int choice);
int determineWinner(int userChoice, int computerChoice);
int getBestOfNumber();
void displayScore(int userScore, int computerScore);
void clearInputBuffer();

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Initialize scores
    int userScore = 0;
    int computerScore = 0;
    int totalGamesPlayed = 0;
    
    cout << "Welcome to Rock, Paper, Scissors!\n";
    
    // Get the number of games to play (best of X)
    int bestOf = getBestOfNumber();
    int gamesToWin = (bestOf / 2) + 1;
    
    cout << "\nFirst to win " << gamesToWin << " games wins the match!\n";
    
    // Main game loop
    while (userScore < gamesToWin && computerScore < gamesToWin) {
        cout << "\nGame " << ++totalGamesPlayed << ":\n";
        
        // Get choices
        int userChoice = getUserChoice();
        int computerChoice = getComputerChoice();
        
        // Display choices
        cout << "\nYou chose: " << convertChoiceToString(userChoice);
        cout << "\nComputer chose: " << convertChoiceToString(computerChoice) << "\n";
        
        // Determine and display winner
        int result = determineWinner(userChoice, computerChoice);
        if (result == 1) {
            cout << "You win this round!\n";
            userScore++;
        } else if (result == -1) {
            cout << "Computer wins this round!\n";
            computerScore++;
        } else {
            cout << "It's a tie!\n";
        }
        
        // Display current score
        displayScore(userScore, computerScore);
    }
    
    // Display final results
    cout << "\n=== Game Over ===\n";
    cout << "Final Score:\n";
    displayScore(userScore, computerScore);
    
    if (userScore > computerScore) {
        cout << "Congratulations! You won the match!\n";
    } else {
        cout << "Computer wins the match! Better luck next time!\n";
    }
    
    return 0;
}

// Function to get user's choice
int getUserChoice() {
    int choice;
    while (true) {
        cout << "\nEnter your choice:\n";
        cout << "1. Rock\n";
        cout << "2. Paper\n";
        cout << "3. Scissors\n";
        cout << "Choice: ";
        
        if (cin >> choice && choice >= 1 && choice <= 3) {
            return choice;
        }
        
        cout << "Invalid input. Please enter 1, 2, or 3.\n";
        clearInputBuffer();
    }
}

// Function to generate computer's choice
int getComputerChoice() {
    return (rand() % 3) + 1;
}

// Function to convert numeric choice to string
string convertChoiceToString(int choice) {
    switch (choice) {
        case 1: return "Rock";
        case 2: return "Paper";
        case 3: return "Scissors";
        default: return "Invalid";
    }
}

// Function to determine the winner
// Returns: 1 for user win, -1 for computer win, 0 for tie
int determineWinner(int userChoice, int computerChoice) {
    if (userChoice == computerChoice) {
        return 0;
    }
    
    if ((userChoice == 1 && computerChoice == 3) ||    // Rock beats Scissors
        (userChoice == 2 && computerChoice == 1) ||    // Paper beats Rock
        (userChoice == 3 && computerChoice == 2)) {    // Scissors beats Paper
        return 1;
    }
    
    return -1;
}

// Function to get the "best of X" number from user
int getBestOfNumber() {
    int n;
    while (true) {
        cout << "Enter an odd number for 'Best of X' games (e.g., 3, 5, 7): ";
        if (cin >> n && n > 0 && n % 2 == 1) {
            return n;
        }
        cout << "Invalid input. Please enter a positive odd number.\n";
        clearInputBuffer();
    }
}

// Function to display current score
void displayScore(int userScore, int computerScore) {
    cout << "\nScore - You: " << userScore << " Computer: " << computerScore << "\n";
}

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
