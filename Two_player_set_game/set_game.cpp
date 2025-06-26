// Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924
// Date: 2025-06-26 (1545pm)
// Description: This is a simple implementation of the Set Game.
// The game is a two-player game where the players take turns to find a set of 3 cards.
// A set is a group of 3 cards where each property is either all the same or all different.
// The player who finds the most sets wins.

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Card structure as specified
struct Card {
    int shape;    // 0: Oval, 1: Squiggle, 2: Diamond
    int color;    // 0: Red, 1: Green, 2: Purple
    int number;   // 0: 1, 1: 2, 2: 3
    int shading;  // 0: Solid, 1: Striped, 2: Open
    
    Card(int s, int c, int n, int sh) : shape(s), color(c), number(n), shading(sh) {}
};

class SetGame {
private:
    vector<Card> deck;
    vector<Card> board;
    int player1Score;
    int player2Score;
    int currentPlayer;
    const int TIMEOUT_SECONDS = 30;
    
    // Card property names for display
    const vector<string> shapes = {"Oval", "Squiggle", "Diamond"};
    const vector<string> colors = {"Red", "Green", "Purple"};
    const vector<string> shadings = {"Solid", "Striped", "Open"};
    
public:
    SetGame() : player1Score(0), player2Score(0), currentPlayer(1) {
        initializeDeck();
        shuffleDeck();
        dealInitialCards();
    }
    
    // Initialize deck with all 81 unique cards (3^4 combinations)
    void initializeDeck() {
        deck.clear();
        for (int shape = 0; shape < 3; shape++) {
            for (int color = 0; color < 3; color++) {
                for (int number = 0; number < 3; number++) {
                    for (int shading = 0; shading < 3; shading++) {
                        deck.emplace_back(shape, color, number, shading);
                    }
                }
            }
        }
    }
    
    // Shuffle the deck using random number generator
    void shuffleDeck() {
        random_device rd;
        mt19937 gen(rd());
        shuffle(deck.begin(), deck.end(), gen);
    }
    
    // Deal initial 12 cards
    void dealInitialCards() {
        board.clear();
        for (int i = 0; i < 12 && !deck.empty(); i++) {
            board.push_back(deck.back());
            deck.pop_back();
        }
    }
    
    // Add 3 more cards to the board
    void addMoreCards() {
        for (int i = 0; i < 3 && !deck.empty(); i++) {
            board.push_back(deck.back());
            deck.pop_back();
        }
    }
    
    // Display a single card
    string cardToString(const Card& card) const {
        return to_string(card.number + 1) + " " + colors[card.color] + " " + 
               shadings[card.shading] + " " + shapes[card.shape];
    }
    
    // Display the game board
    void displayBoard() const {
        cout << "\nCards on table:\n";
        for (size_t i = 0; i < board.size(); i++) {
            cout << "[" << i << "] " << cardToString(board[i]) << "\n";
        }
        cout << "\n";
    }
    
    // Display game status
    void displayStatus() const {
        cout << "=== Set Game ===\n";
        cout << "Player " << currentPlayer << "'s Turn | Score: P1 - " << player1Score 
             << " | P2 - " << player2Score << "\n";
        cout << "Cards in deck: " << deck.size() << "\n";
    }
    
    // Check if three cards form a valid Set
    bool isValidSet(const Card& card1, const Card& card2, const Card& card3) const {
        // Check each property: all same OR all different
        bool shapeValid = (card1.shape == card2.shape && card2.shape == card3.shape) ||
                         (card1.shape != card2.shape && card2.shape != card3.shape && card1.shape != card3.shape);
        
        bool colorValid = (card1.color == card2.color && card2.color == card3.color) ||
                         (card1.color != card2.color && card2.color != card3.color && card1.color != card3.color);
        
        bool numberValid = (card1.number == card2.number && card2.number == card3.number) ||
                          (card1.number != card2.number && card2.number != card3.number && card1.number != card3.number);
        
        bool shadingValid = (card1.shading == card2.shading && card2.shading == card3.shading) ||
                           (card1.shading != card2.shading && card2.shading != card3.shading && card1.shading != card3.shading);
        
        return shapeValid && colorValid && numberValid && shadingValid;
    }
    
    // Find all possible Sets on the board
    vector<vector<int>> findAllSets() const {
        vector<vector<int>> sets;
        
        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = i + 1; j < board.size(); j++) {
                for (size_t k = j + 1; k < board.size(); k++) {
                    if (isValidSet(board[i], board[j], board[k])) {
                        sets.push_back({static_cast<int>(i), static_cast<int>(j), static_cast<int>(k)});
                    }
                }
            }
        }
        
        return sets;
    }
    
    // Remove cards from board and replace with new ones
    void removeAndReplaceCards(const vector<int>& cardIndices) {
        // Sort indices in descending order to avoid index shifting issues
        vector<int> sortedIndices = cardIndices;
        sort(sortedIndices.rbegin(), sortedIndices.rend());
        
        // Remove the selected cards
        for (int index : sortedIndices) {
            board.erase(board.begin() + index);
        }
        
        // Add new cards if deck has cards
        for (int i = 0; i < 3 && !deck.empty(); i++) {
            board.push_back(deck.back());
            deck.pop_back();
        }
    }
    
    // Get player input with timeout
    vector<int> getPlayerInput() {
        vector<int> selectedCards;
        string input;
        
        cout << "Enter 3 card numbers (e.g., 1 4 7): ";
        
        // Start timer
        auto start = chrono::steady_clock::now();
        
        // Check for input with timeout
        while (chrono::steady_clock::now() - start < chrono::seconds(TIMEOUT_SECONDS)) {
            if (cin.rdbuf()->in_avail()) {
                getline(cin, input);
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        // Check if timeout occurred
        if (chrono::steady_clock::now() - start >= chrono::seconds(TIMEOUT_SECONDS)) {
            cout << "\n⏰ Time up! No input received.\n";
            return {};
        }
        
        // Parse input
        stringstream ss(input);
        int cardIndex;
        while (ss >> cardIndex) {
            selectedCards.push_back(cardIndex);
        }
        
        return selectedCards;
    }
    
    // Validate player input
    bool validateInput(const vector<int>& selectedCards) {
        if (selectedCards.size() != 3) {
            cout << "Please select exactly 3 cards.\n";
            return false;
        }
        
        for (int index : selectedCards) {
            if (index < 0 || index >= static_cast<int>(board.size())) {
                cout << "Invalid card index: " << index << "\n";
                return false;
            }
        }
        
        // Check for duplicate indices
        if (selectedCards[0] == selectedCards[1] || selectedCards[1] == selectedCards[2] || selectedCards[0] == selectedCards[2]) {
            cout << "Please select 3 different cards.\n";
            return false;
        }
        
        return true;
    }
    
    // Play a single turn
    void playTurn() {
        displayStatus();
        displayBoard();
        
        vector<int> selectedCards = getPlayerInput();
        
        if (selectedCards.empty()) {
            // Timeout occurred, show all possible sets
            vector<vector<int>> allSets = findAllSets();
            cout << "Computer says: Possible Sets are: ";
            if (allSets.empty()) {
                cout << "None found!";
            } else {
                for (size_t i = 0; i < allSets.size(); i++) {
                    cout << "(" << allSets[i][0] << "," << allSets[i][1] << "," << allSets[i][2] << ")";
                    if (i < allSets.size() - 1) cout << ", ";
                }
            }
            cout << "\n";
            
            // If no sets found, add more cards
            if (allSets.empty() && !deck.empty()) {
                cout << "No sets found. Adding 3 more cards...\n";
                addMoreCards();
            }
        } else {
            // Validate input
            if (!validateInput(selectedCards)) {
                cout << "Invalid input. Turn skipped.\n";
                return;
            }
            
            // Check if selected cards form a valid set
            Card card1 = board[selectedCards[0]];
            Card card2 = board[selectedCards[1]];
            Card card3 = board[selectedCards[2]];
            
            if (isValidSet(card1, card2, card3)) {
                cout << "Valid Set found! Cards: " << cardToString(card1) << ", " 
                     << cardToString(card2) << ", " << cardToString(card3) << "\n";
                
                // Award point
                if (currentPlayer == 1) player1Score++;
                else player2Score++;
                
                // Remove and replace cards
                removeAndReplaceCards(selectedCards);
                
                cout << "Player " << currentPlayer << " earns 1 point!\n";
            } else {
                cout << "Invalid Set. Turn skipped.\n";
            }
        }
        
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        
        // Switch players
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    
    // Check if game is over
    bool isGameOver() const {
        if (!deck.empty()) return false;
        
        vector<vector<int>> remainingSets = findAllSets();
        return remainingSets.empty();
    }
    
    // Display final results
    void displayFinalResults() const {
        cout << "\n=== Game Over ===\n";
        cout << "Final Score: Player 1 - " << player1Score << " | Player 2 - " << player2Score << "\n";
        
        if (player1Score > player2Score) {
            cout << "Player 1 wins!\n";
        } else if (player2Score > player1Score) {
            cout << "Player 2 wins!\n";
        } else {
            cout << "It's a tie!\n";
        }
    }
    
    // Main game loop
    void run() {
        cout << "Welcome to Set Game!\n";
        cout << "Each player has 30 seconds to find a Set.\n";
        cout << "A Set consists of 3 cards where each property is either all the same or all different.\n\n";
        
        while (!isGameOver()) {
            playTurn();
        }
        
        displayFinalResults();
    }
};

int main() {
    SetGame game;
    game.run();
    return 0;
} 