CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = contain_the_spread
SOURCE = contain_the_spread.cpp

# Default target
all: $(TARGET)

# Compile the game
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean build files
clean:
	rm -f $(TARGET).exe $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required for this game."

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the game (default)"
	@echo "  clean   - Remove build files"
	@echo "  run     - Build and run the game"
	@echo "  install - Install dependencies"
	@echo "  help    - Show this help message"

.PHONY: all clean run install help 