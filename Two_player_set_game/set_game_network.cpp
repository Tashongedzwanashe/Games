// Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924
// Date: 2025-06-26 (1545pm)
// Description: Set Game Network Multiplayer Extension
// This version supports multiplayer over network with client-server architecture

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;

// Card structure as specified
struct Card {
    int shape;    // 0: Oval, 1: Squiggle, 2: Diamond
    int color;    // 0: Red, 1: Green, 2: Purple
    int number;   // 0: 1, 1: 2, 2: 3
    int shading;  // 0: Solid, 1: Striped, 2: Open
    
    Card(int s, int c, int n, int sh) : shape(s), color(c), number(n), shading(sh) {}
};

class SetGameNetwork {
private:
    vector<Card> deck;
    vector<Card> board;
    int player1Score;
    int player2Score;
    int currentPlayer;
    bool isServer;
    bool isConnected;
    TcpListener listener;
    TcpSocket clientSocket;
    TcpSocket serverSocket;
    
    // Card property names for display
    const vector<string> shapes = {"Oval", "Squiggle", "Diamond"};
    const vector<string> colors = {"Red", "Green", "Purple"};
    const vector<string> shadings = {"Solid", "Striped", "Open"};
    
public:
    SetGameNetwork() : player1Score(0), player2Score(0), currentPlayer(1), 
                       isServer(false), isConnected(false) {
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
        cout << "=== Set Game Network ===\n";
        cout << "Mode: " << (isServer ? "Server" : "Client") << "\n";
        cout << "Connection: " << (isConnected ? "Connected" : "Disconnected") << "\n";
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
    
    // Start server
    bool startServer(unsigned short port) {
        isServer = true;
        
        if (listener.listen(port) != Socket::Done) {
            cout << "Failed to start server on port " << port << "\n";
            return false;
        }
        
        cout << "Server started on port " << port << ". Waiting for client...\n";
        
        if (listener.accept(serverSocket) != Socket::Done) {
            cout << "Failed to accept client connection\n";
            return false;
        }
        
        isConnected = true;
        cout << "Client connected!\n";
        return true;
    }
    
    // Connect to server
    bool connectToServer(const string& address, unsigned short port) {
        isServer = false;
        
        if (clientSocket.connect(address, port) != Socket::Done) {
            cout << "Failed to connect to server " << address << ":" << port << "\n";
            return false;
        }
        
        isConnected = true;
        cout << "Connected to server!\n";
        return true;
    }
    
    // Send game state to other player
    void sendGameState() {
        if (!isConnected) return;
        
        Packet packet;
        packet << static_cast<Uint32>(board.size());
        for (const auto& card : board) {
            packet << card.shape << card.color << card.number << card.shading;
        }
        packet << player1Score << player2Score << currentPlayer << static_cast<Uint32>(deck.size());
        
        if (isServer) {
            serverSocket.send(packet);
        } else {
            clientSocket.send(packet);
        }
    }
    
    // Receive game state from other player
    bool receiveGameState() {
        if (!isConnected) return false;
        
        Packet packet;
        Socket::Status status;
        
        if (isServer) {
            status = serverSocket.receive(packet);
        } else {
            status = clientSocket.receive(packet);
        }
        
        if (status == Socket::Done) {
            Uint32 boardSize;
            packet >> boardSize;
            board.clear();
            
            for (Uint32 i = 0; i < boardSize; i++) {
                int shape, color, number, shading;
                packet >> shape >> color >> number >> shading;
                board.emplace_back(shape, color, number, shading);
            }
            
            packet >> player1Score >> player2Score >> currentPlayer;
            
            Uint32 deckSize;
            packet >> deckSize;
            // Note: We don't sync the deck, just the size for display
            
            return true;
        }
        
        return false;
    }
    
    // Send player move to other player
    void sendPlayerMove(const vector<int>& selectedCards) {
        if (!isConnected) return;
        
        Packet packet;
        packet << static_cast<Uint32>(selectedCards.size());
        for (int card : selectedCards) {
            packet << card;
        }
        
        if (isServer) {
            serverSocket.send(packet);
        } else {
            clientSocket.send(packet);
        }
    }
    
    // Receive player move from other player
    vector<int> receivePlayerMove() {
        vector<int> selectedCards;
        
        if (!isConnected) return selectedCards;
        
        Packet packet;
        Socket::Status status;
        
        if (isServer) {
            status = serverSocket.receive(packet);
        } else {
            status = clientSocket.receive(packet);
        }
        
        if (status == Socket::Done) {
            Uint32 cardsSize;
            packet >> cardsSize;
            
            for (Uint32 i = 0; i < cardsSize; i++) {
                int card;
                packet >> card;
                selectedCards.push_back(card);
            }
        }
        
        return selectedCards;
    }
    
    // Get player input
    vector<int> getPlayerInput() {
        vector<int> selectedCards;
        string input;
        
        cout << "Enter 3 card numbers (e.g., 1 4 7): ";
        getline(cin, input);
        
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
    
    // Process player move
    void processPlayerMove(const vector<int>& selectedCards) {
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
        
        // Switch players
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    
    // Play a single turn
    void playTurn() {
        displayStatus();
        displayBoard();
        
        // Check if it's this player's turn
        int myPlayer = isServer ? 1 : 2;
        if (currentPlayer != myPlayer) {
            cout << "Waiting for other player's move...\n";
            
            // Receive move from other player
            vector<int> receivedMove = receivePlayerMove();
            if (!receivedMove.empty()) {
                processPlayerMove(receivedMove);
            }
            
            this_thread::sleep_for(chrono::milliseconds(1000));
            return;
        }
        
        vector<int> selectedCards = getPlayerInput();
        
        if (selectedCards.empty()) {
            // Show hint
            vector<vector<int>> allSets = findAllSets();
            cout << "Possible Sets are: ";
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
            // Send move to other player
            sendPlayerMove(selectedCards);
            processPlayerMove(selectedCards);
        }
        
        // Send updated game state
        sendGameState();
        
        cout << "Press Enter to continue...";
        cin.get();
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
        cout << "Welcome to Set Game Network!\n";
        cout << "Choose mode:\n";
        cout << "1. Start Server\n";
        cout << "2. Connect to Server\n";
        cout << "Enter choice (1-2): ";
        
        int choice;
        cin >> choice;
        cin.ignore(); // Clear newline
        
        if (choice == 1) {
            cout << "Enter port number: ";
            unsigned short port;
            cin >> port;
            cin.ignore();
            
            if (!startServer(port)) {
                return;
            }
        } else if (choice == 2) {
            cout << "Enter server address: ";
            string address;
            getline(cin, address);
            
            cout << "Enter port number: ";
            unsigned short port;
            cin >> port;
            cin.ignore();
            
            if (!connectToServer(address, port)) {
                return;
            }
        } else {
            cout << "Invalid choice.\n";
            return;
        }
        
        cout << "Each player has 30 seconds to find a Set.\n";
        cout << "A Set consists of 3 cards where each property is either all the same or all different.\n\n";
        
        while (!isGameOver()) {
            playTurn();
        }
        
        displayFinalResults();
    }
};

int main() {
    SetGameNetwork game;
    game.run();
    return 0;
} 