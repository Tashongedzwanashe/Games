CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = set_game
SOURCE = set_game.cpp

# Default target
all: $(TARGET)

# Compile the game
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean build files
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the game
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required. Using only C++ standard library."

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the Set game (default)"
	@echo "  clean   - Remove build files"
	@echo "  run     - Build and run the game"
	@echo "  install - Show dependency info"
	@echo "  help    - Show this help message"

.PHONY: all clean run install help 