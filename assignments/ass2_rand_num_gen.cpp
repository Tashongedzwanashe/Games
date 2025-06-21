#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

// Structure to store performance metrics
struct PerformanceMetrics {
    double execution_time_ms;
    size_t memory_usage_bytes;
    std::string method_name;
    int n;
    std::string distribution_type;
};

// Function to generate uniform integers between 1 and 100
template<typename T>
void generate_uniform_integers(T* data, int n, std::mt19937& gen) {
    std::uniform_int_distribution<int> dist(1, 100);
    for (int i = 0; i < n; ++i) {
        data[i] = static_cast<T>(dist(gen));
    }
}

// Function to generate uniform floating-point numbers between 0.0 and 1.0
template<typename T>
void generate_uniform_floats(T* data, int n, std::mt19937& gen) {
    std::uniform_real_distribution<T> dist(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        data[i] = dist(gen);
    }
}

// Function to measure performance for a given method and size
template<typename T>
PerformanceMetrics measure_performance(const std::string& method_name, int n, 
                                      const std::string& distribution_type,
                                      std::mt19937& gen) {
    PerformanceMetrics metrics;
    metrics.method_name = method_name;
    metrics.n = n;
    metrics.distribution_type = distribution_type;
    
    T* data = nullptr;
    
    // Allocate memory based on method
    if (method_name == "Static Array") {
        if (n <= 1000) { // Only for small n
            static T static_data[1000];
            data = static_data;
        } else {
            std::cout << "Static array not suitable for n = " << n << std::endl;
            metrics.execution_time_ms = -1;
            metrics.memory_usage_bytes = 0;
            return metrics;
        }
    } else if (method_name == "Dynamic Array") {
        data = new T[n];
    } else if (method_name == "std::vector") {
        // Will be handled separately
    } else if (method_name == "Manual Allocation") {
        data = static_cast<T*>(malloc(n * sizeof(T)));
    }
    
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    
    // Generate random numbers
    if (method_name == "std::vector") {
        std::vector<T> vec(n);
        if (distribution_type == "Integer") {
            generate_uniform_integers(vec.data(), n, gen);
        } else {
            generate_uniform_floats(vec.data(), n, gen);
        }
    } else {
        if (distribution_type == "Integer") {
            generate_uniform_integers(data, n, gen);
        } else {
            generate_uniform_floats(data, n, gen);
        }
    }
    
    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    metrics.execution_time_ms = duration.count() / 1000.0;
    
    // Calculate memory usage
    metrics.memory_usage_bytes = n * sizeof(T);
    
    // Cleanup
    if (method_name == "Dynamic Array") {
        delete[] data;
    } else if (method_name == "Manual Allocation") {
        free(data);
    }
    
    return metrics;
}

// Function to save data to CSV for plotting
void save_data_to_csv(const std::vector<PerformanceMetrics>& metrics, 
                      const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    file << "Method,Size,Distribution,ExecutionTime(ms),MemoryUsage(bytes)\n";
    for (const auto& metric : metrics) {
        if (metric.execution_time_ms >= 0) {
            file << metric.method_name << ","
                 << metric.n << ","
                 << metric.distribution_type << ","
                 << std::fixed << std::setprecision(6) << metric.execution_time_ms << ","
                 << metric.memory_usage_bytes << "\n";
        }
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

// Function to generate sample data for histogram plotting
void generate_sample_data_for_histogram(int n, const std::string& distribution_type, 
                                       const std::string& filename) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::vector<double> data(n);
    
    if (distribution_type == "Integer") {
        std::uniform_int_distribution<int> dist(1, 100);
        for (int i = 0; i < n; ++i) {
            data[i] = static_cast<double>(dist(gen));
        }
    } else {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            data[i] = dist(gen);
        }
    }
    
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Value\n";
        for (double val : data) {
            file << std::fixed << std::setprecision(6) << val << "\n";
        }
        file.close();
        std::cout << "Sample data for histogram saved to " << filename << std::endl;
    }
}

int main() {
    std::cout << "Random Number Generator Performance Analysis\n";
    std::cout << "============================================\n\n";
    
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Test sizes
    std::vector<int> sizes = {1000, 10000, 100000};
    
    // Storage methods
    std::vector<std::string> methods = {"Static Array", "Dynamic Array", "std::vector", "Manual Allocation"};
    
    // Distribution types
    std::vector<std::string> distributions = {"Integer", "Float"};
    
    std::vector<PerformanceMetrics> all_metrics;
    
    // Run performance tests
    for (const auto& size : sizes) {
        std::cout << "Testing size n = " << size << std::endl;
        std::cout << "----------------------------------------\n";
        
        for (const auto& method : methods) {
            for (const auto& dist_type : distributions) {
                std::cout << "Method: " << method << ", Distribution: " << dist_type;
                
                if (dist_type == "Integer") {
                    auto metrics = measure_performance<int>(method, size, dist_type, gen);
                    all_metrics.push_back(metrics);
                    
                    if (metrics.execution_time_ms >= 0) {
                        std::cout << " - Time: " << std::fixed << std::setprecision(3) 
                                 << metrics.execution_time_ms << " ms, Memory: " 
                                 << metrics.memory_usage_bytes << " bytes";
                    } else {
                        std::cout << " - Not applicable";
                    }
                } else {
                    auto metrics = measure_performance<double>(method, size, dist_type, gen);
                    all_metrics.push_back(metrics);
                    
                    if (metrics.execution_time_ms >= 0) {
                        std::cout << " - Time: " << std::fixed << std::setprecision(3) 
                                 << metrics.execution_time_ms << " ms, Memory: " 
                                 << metrics.memory_usage_bytes << " bytes";
                    } else {
                        std::cout << " - Not applicable";
                    }
                }
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    
    // Save performance data to CSV
    save_data_to_csv(all_metrics, "performance_data.csv");
    
    // Generate sample data for histogram plotting
    generate_sample_data_for_histogram(10000, "Integer", "integer_sample.csv");
    generate_sample_data_for_histogram(10000, "Float", "float_sample.csv");
    
    // Print summary
    std::cout << "\nSummary:\n";
    std::cout << "========\n";
    std::cout << "Performance data saved to: performance_data.csv\n";
    std::cout << "Sample integer data saved to: integer_sample.csv\n";
    std::cout << "Sample float data saved to: float_sample.csv\n\n";
    
    std::cout << "Use these files with Python/matplotlib or other plotting tools to create:\n";
    std::cout << "1. Histograms of the generated values\n";
    std::cout << "2. Execution time vs. n plots\n";
    std::cout << "3. Memory usage vs. n plots\n";
    
    return 0;
}
