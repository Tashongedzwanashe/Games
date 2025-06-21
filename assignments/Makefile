# Makefile for Random Number Generator Performance Analysis

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# Target executable
TARGET = ass2_rand_num_gen

# Source files
SOURCES = ass2_rand_num_gen.cpp

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with Python analysis
analyze: run
	python plot_results.py

# Clean build files
clean:
	rm -f $(TARGET) *.csv *.png

# Install Python dependencies (if needed)
install-deps:
	pip install pandas matplotlib numpy seaborn

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Compile the program"
	@echo "  run      - Compile and run the program"
	@echo "  analyze  - Run program and generate plots"
	@echo "  clean    - Remove build files and generated data"
	@echo "  install-deps - Install Python dependencies"
	@echo "  help     - Show this help message"

.PHONY: all run analyze clean install-deps help 