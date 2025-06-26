#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

// Simple function to generate random integers between 1 and 100
void generate_random_integers(int* array, int size) {
    std::random_device rd;  // Get a random seed
    std::mt19937 gen(rd()); // Create random number generator
    std::uniform_int_distribution<int> dist(1, 100); // Distribution from 1 to 100
    
    for (int i = 0; i < size; i++) {
        array[i] = dist(gen); // Generate random number and store it
    }
}

// Simple function to generate random floats between 0.0 and 1.0
void generate_random_floats(double* array, int size) {
    std::random_device rd;  // Get a random seed
    std::mt19937 gen(rd()); // Create random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0); // Distribution from 0.0 to 1.0
    
    for (int i = 0; i < size; i++) {
        array[i] = dist(gen); // Generate random number and store it
    }
}

// Function to print array contents (first 10 numbers)
void print_array(int* array, int size, const std::string& name) {
    std::cout << name << " (first 10 numbers): ";
    for (int i = 0; i < std::min(size, 10); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void print_array(double* array, int size, const std::string& name) {
    std::cout << name << " (first 10 numbers): ";
    for (int i = 0; i < std::min(size, 10); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// Function to measure time for generating random numbers
double measure_time(int size, const std::string& method_name) {
    auto start = std::chrono::high_resolution_clock::now();
    
    if (method_name == "Static Array") {
        int static_array[1000];
        generate_random_integers(static_array, size);
    } else if (method_name == "Dynamic Array") {
        int* dynamic_array = new int[size];
        generate_random_integers(dynamic_array, size);
        delete[] dynamic_array;
    } else if (method_name == "std::vector") {
        std::vector<int> vector_array(size);
        generate_random_integers(vector_array.data(), size);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1000.0; // Convert to milliseconds
}

int main() {
    std::cout << "Simple Random Number Generator\n";
    std::cout << "==============================\n\n";
    
    int size = 1000;
    
    // Method 1: Static Array
    std::cout << "Method 1: Static Array\n";
    std::cout << "----------------------\n";
    int static_array[1000];
    generate_random_integers(static_array, size);
    print_array(static_array, size, "Static Array");
    
    // Method 2: Dynamic Array
    std::cout << "\nMethod 2: Dynamic Array\n";
    std::cout << "----------------------\n";
    int* dynamic_array = new int[size];
    generate_random_integers(dynamic_array, size);
    print_array(dynamic_array, size, "Dynamic Array");
    delete[] dynamic_array; // Don't forget to free memory!
    
    // Method 3: std::vector
    std::cout << "\nMethod 3: std::vector\n";
    std::cout << "----------------------\n";
    std::vector<int> vector_array(size);
    generate_random_integers(vector_array.data(), size);
    print_array(vector_array.data(), size, "std::vector");
    
    // Method 4: Float numbers
    std::cout << "\nMethod 4: Float Numbers\n";
    std::cout << "----------------------\n";
    double* float_array = new double[size];
    generate_random_floats(float_array, size);
    print_array(float_array, size, "Float Array");
    delete[] float_array;
    
    // Performance comparison
    std::cout << "\nPerformance Comparison\n";
    std::cout << "======================\n";
    
    std::vector<std::string> methods = {"Static Array", "Dynamic Array", "std::vector"};
    std::vector<int> sizes = {1000, 10000, 100000};
    
    for (int test_size : sizes) {
        std::cout << "\nTesting with size: " << test_size << std::endl;
        std::cout << "------------------------\n";
        
        for (const std::string& method : methods) {
            if (method == "Static Array" && test_size > 1000) {
                std::cout << method << ": Not suitable for large sizes\n";
                continue;
            }
            
            double time_ms = measure_time(test_size, method);
            std::cout << method << ": " << std::fixed << std::setprecision(3) 
                     << time_ms << " ms\n";
        }
    }
    
    std::cout << "\nSummary:\n";
    std::cout << "========\n";
    std::cout << "• Static Array: Fastest but limited size\n";
    std::cout << "• Dynamic Array: Good performance, manual memory management\n";
    std::cout << "• std::vector: Most convenient, automatic memory management\n";
    std::cout << "• All methods generate the same quality random numbers\n";
    
    return 0;
}
