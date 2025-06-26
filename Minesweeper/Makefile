CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = minesweeper
SOURCE = minesweeper.cpp

# Default target
all: $(TARGET)

# Compile the game
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean compiled files
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the game
run: $(TARGET)
	./$(TARGET)

# Debug version
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean run debug 