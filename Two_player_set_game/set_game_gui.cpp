// Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924
// Date: 2025-06-26 (1545pm)
// Description: Set Game GUI Extension using SFML
// This version provides a graphical user interface for the Set Game

#include <SFML/Graphics.hpp>
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

class SetGameGUI {
private:
    RenderWindow window;
    Font font;
    
    vector<Card> deck;
    vector<Card> board;
    int player1Score;
    int player2Score;
    int currentPlayer;
    vector<int> selectedCards;
    bool gameOver;
    string gameMessage;
    float messageTimer;
    
    // Card visual properties
    const float CARD_WIDTH = 120.0f;
    const float CARD_HEIGHT = 80.0f;
    const float CARD_SPACING = 20.0f;
    const float BOARD_START_X = 50.0f;
    const float BOARD_START_Y = 150.0f;
    const int CARDS_PER_ROW = 4;
    
    // Colors
    Color cardColor = Color(240, 240, 240);
    Color selectedColor = Color(255, 255, 0, 100);
    Color borderColor = Color(100, 100, 100);
    Color textColor = Color(50, 50, 50);
    Color redColor = Color(255, 0, 0);
    Color greenColor = Color(0, 255, 0);
    Color purpleColor = Color(128, 0, 128);
    
public:
    SetGameGUI() : window(VideoMode(800, 600), "Set Game"), 
                   player1Score(0), player2Score(0), currentPlayer(1), 
                   gameOver(false), messageTimer(0.0f) {
        window.setFramerateLimit(60);
        
        // Load font
        if (!font.loadFromFile("arial.ttf")) {
            cout << "Error loading font. Using system font.\n";
        }
        
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
    
    // Get card color
    Color getCardColor(int colorIndex) const {
        switch (colorIndex) {
            case 0: return redColor;
            case 1: return greenColor;
            case 2: return purpleColor;
            default: return Color::Black;
        }
    }
    
    // Draw a card
    void drawCard(const Card& card, float x, float y, bool selected) {
        // Card background
        RectangleShape cardRect(Vector2f(CARD_WIDTH, CARD_HEIGHT));
        cardRect.setPosition(x, y);
        cardRect.setFillColor(selected ? selectedColor : cardColor);
        cardRect.setOutlineColor(borderColor);
        cardRect.setOutlineThickness(2.0f);
        window.draw(cardRect);
        
        // Card content
        Color symbolColor = getCardColor(card.color);
        
        // Draw symbols based on number
        for (int i = 0; i < card.number + 1; i++) {
            float symbolX = x + 20.0f + i * 25.0f;
            float symbolY = y + CARD_HEIGHT / 2 - 10.0f;
            
            // Draw shape
            if (card.shape == 0) { // Oval
                CircleShape oval(8.0f, 8.0f);
                oval.setPosition(symbolX, symbolY);
                oval.setFillColor(symbolColor);
                if (card.shading == 1) { // Striped
                    oval.setFillColor(Color(symbolColor.r, symbolColor.g, symbolColor.b, 128));
                } else if (card.shading == 2) { // Open
                    oval.setFillColor(Color::Transparent);
                    oval.setOutlineColor(symbolColor);
                    oval.setOutlineThickness(2.0f);
                }
                window.draw(oval);
            } else if (card.shape == 1) { // Squiggle
                RectangleShape squiggle(Vector2f(16.0f, 8.0f));
                squiggle.setPosition(symbolX, symbolY);
                squiggle.setFillColor(symbolColor);
                if (card.shading == 1) { // Striped
                    squiggle.setFillColor(Color(symbolColor.r, symbolColor.g, symbolColor.b, 128));
                } else if (card.shading == 2) { // Open
                    squiggle.setFillColor(Color::Transparent);
                    squiggle.setOutlineColor(symbolColor);
                    squiggle.setOutlineThickness(2.0f);
                }
                window.draw(squiggle);
            } else if (card.shape == 2) { // Diamond
                ConvexShape diamond;
                diamond.setPointCount(4);
                diamond.setPoint(0, Vector2f(symbolX + 8.0f, symbolY));
                diamond.setPoint(1, Vector2f(symbolX + 16.0f, symbolY + 8.0f));
                diamond.setPoint(2, Vector2f(symbolX + 8.0f, symbolY + 16.0f));
                diamond.setPoint(3, Vector2f(symbolX, symbolY + 8.0f));
                diamond.setFillColor(symbolColor);
                if (card.shading == 1) { // Striped
                    diamond.setFillColor(Color(symbolColor.r, symbolColor.g, symbolColor.b, 128));
                } else if (card.shading == 2) { // Open
                    diamond.setFillColor(Color::Transparent);
                    diamond.setOutlineColor(symbolColor);
                    diamond.setOutlineThickness(2.0f);
                }
                window.draw(diamond);
            }
        }
    }
    
    // Draw the game board
    void drawBoard() {
        for (size_t i = 0; i < board.size(); i++) {
            int row = i / CARDS_PER_ROW;
            int col = i % CARDS_PER_ROW;
            float x = BOARD_START_X + col * (CARD_WIDTH + CARD_SPACING);
            float y = BOARD_START_Y + row * (CARD_HEIGHT + CARD_SPACING);
            
            bool selected = find(selectedCards.begin(), selectedCards.end(), i) != selectedCards.end();
            drawCard(board[i], x, y, selected);
        }
    }
    
    // Draw UI elements
    void drawUI() {
        // Title
        Text title("Set Game", font, 32);
        title.setPosition(20, 20);
        title.setFillColor(textColor);
        window.draw(title);
        
        // Scores
        Text scoreText("Player 1: " + to_string(player1Score) + " | Player 2: " + to_string(player2Score), font, 18);
        scoreText.setPosition(20, 60);
        scoreText.setFillColor(textColor);
        window.draw(scoreText);
        
        // Current player
        Text playerText("Current Player: " + to_string(currentPlayer), font, 18);
        playerText.setPosition(20, 85);
        playerText.setFillColor(textColor);
        window.draw(playerText);
        
        // Deck count
        Text deckText("Cards in deck: " + to_string(deck.size()), font, 16);
        deckText.setPosition(20, 110);
        deckText.setFillColor(textColor);
        window.draw(deckText);
        
        // Instructions
        Text instructions("Click 3 cards to form a Set. Press H for hint, A to add cards.", font, 14);
        instructions.setPosition(20, 550);
        instructions.setFillColor(textColor);
        window.draw(instructions);
        
        // Game message
        if (!gameMessage.empty() && messageTimer > 0) {
            Text message(gameMessage, font, 20);
            message.setPosition(400 - message.getLocalBounds().width / 2, 500);
            message.setFillColor(Color::Red);
            window.draw(message);
        }
    }
    
    // Handle mouse click
    void handleMouseClick(int mouseX, int mouseY) {
        if (gameOver) return;
        
        // Check if click is on a card
        for (size_t i = 0; i < board.size(); i++) {
            int row = i / CARDS_PER_ROW;
            int col = i % CARDS_PER_ROW;
            float x = BOARD_START_X + col * (CARD_WIDTH + CARD_SPACING);
            float y = BOARD_START_Y + row * (CARD_HEIGHT + CARD_SPACING);
            
            if (mouseX >= x && mouseX <= x + CARD_WIDTH &&
                mouseY >= y && mouseY <= y + CARD_HEIGHT) {
                
                // Toggle selection
                auto it = find(selectedCards.begin(), selectedCards.end(), i);
                if (it != selectedCards.end()) {
                    selectedCards.erase(it);
                } else {
                    if (selectedCards.size() < 3) {
                        selectedCards.push_back(i);
                    }
                }
                
                // Check if we have 3 selected cards
                if (selectedCards.size() == 3) {
                    checkSet();
                }
                
                break;
            }
        }
    }
    
    // Check if selected cards form a valid set
    void checkSet() {
        if (selectedCards.size() != 3) return;
        
        Card card1 = board[selectedCards[0]];
        Card card2 = board[selectedCards[1]];
        Card card3 = board[selectedCards[2]];
        
        if (isValidSet(card1, card2, card3)) {
            // Valid set found
            if (currentPlayer == 1) player1Score++;
            else player2Score++;
            
            removeAndReplaceCards(selectedCards);
            selectedCards.clear();
            
            gameMessage = "Valid Set! Player " + to_string(currentPlayer) + " scores!";
            messageTimer = 3.0f;
            
            // Switch players
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            // Invalid set
            gameMessage = "Invalid Set! Try again.";
            messageTimer = 2.0f;
            selectedCards.clear();
        }
    }
    
    // Handle keyboard input
    void handleKeyPress(Keyboard::Key key) {
        switch (key) {
            case Keyboard::H: // Hint
                showHint();
                break;
            case Keyboard::A: // Add cards
                if (findAllSets().empty() && !deck.empty()) {
                    addMoreCards();
                    gameMessage = "Added 3 more cards.";
                    messageTimer = 2.0f;
                }
                break;
            case Keyboard::R: // Reset game
                resetGame();
                break;
        }
    }
    
    // Show hint
    void showHint() {
        vector<vector<int>> allSets = findAllSets();
        if (!allSets.empty()) {
            gameMessage = "Hint: There are " + to_string(allSets.size()) + " possible sets.";
        } else {
            gameMessage = "No sets found. Press A to add more cards.";
        }
        messageTimer = 3.0f;
    }
    
    // Reset game
    void resetGame() {
        player1Score = 0;
        player2Score = 0;
        currentPlayer = 1;
        selectedCards.clear();
        gameOver = false;
        gameMessage.clear();
        messageTimer = 0.0f;
        
        initializeDeck();
        shuffleDeck();
        dealInitialCards();
    }
    
    // Check if game is over
    void checkGameOver() {
        if (!deck.empty()) return;
        
        vector<vector<int>> remainingSets = findAllSets();
        if (remainingSets.empty()) {
            gameOver = true;
            if (player1Score > player2Score) {
                gameMessage = "Game Over! Player 1 wins!";
            } else if (player2Score > player1Score) {
                gameMessage = "Game Over! Player 2 wins!";
            } else {
                gameMessage = "Game Over! It's a tie!";
            }
            messageTimer = 10.0f; // Show for 10 seconds
        }
    }
    
    // Main game loop
    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button == Mouse::Left) {
                            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                        }
                        break;
                    case Event::KeyPressed:
                        handleKeyPress(event.key.code);
                        break;
                }
            }
            
            // Update message timer
            if (messageTimer > 0) {
                messageTimer -= 1.0f / 60.0f; // Assuming 60 FPS
                if (messageTimer <= 0) {
                    gameMessage.clear();
                }
            }
            
            // Check game over
            checkGameOver();
            
            // Clear window
            window.clear(Color(220, 220, 220));
            
            // Draw game elements
            drawBoard();
            drawUI();
            
            // Display
            window.display();
        }
    }
};

int main() {
    SetGameGUI game;
    game.run();
    return 0;
} 