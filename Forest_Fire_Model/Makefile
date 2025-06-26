# Makefile for Forest Fire Simulation

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = forest_fire

# Source files
SOURCES = forest_fire.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the simulation
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build
release: CXXFLAGS += -O3 -DNDEBUG
release: $(TARGET)

# Install (copy to system path)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the forest fire simulation (default)"
	@echo "  clean    - Remove build files"
	@echo "  run      - Build and run the simulation"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized release version"
	@echo "  install  - Install to system path"
	@echo "  uninstall- Remove from system path"
	@echo "  help     - Show this help message"

.PHONY: all clean run debug release install uninstall help 