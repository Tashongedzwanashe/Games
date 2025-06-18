#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

// Function to print execution time with consistent formatting
void printExecutionTime(const string& operation, 
                       chrono::duration<double, milli> duration) {
    cout << setw(30) << left << operation 
              << ": " << duration.count() << " ms" << endl;
}

// Function template to print array elements (works for both raw arrays and vectors)
template<typename T>
void printElements(const T& arr, size_t size, const string& arrayType) {
    auto start = chrono::high_resolution_clock::now();
    
    cout << "\nFirst 10 elements of " << arrayType << ": ";
    for (size_t i = 0; i < min(size_t(10), size); ++i) {
        cout << arr[i] << " ";
    }
    cout << "..." << endl;
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    printExecutionTime("Print (first 10 elements)", duration);
}

// Function to perform operations on raw array
void analyzeRawArray(const size_t SIZE, const int MIN_VAL, const int MAX_VAL) {
    cout << "\n=== Raw Array Analysis ===\n";
    
    // Allocate dynamic array
    auto start = chrono::high_resolution_clock::now();
    int* arr = new int[SIZE];
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    printExecutionTime("Memory allocation", duration);

    // Generate random numbers
    start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(MIN_VAL, MAX_VAL);
    for (size_t i = 0; i < SIZE; ++i) {
        arr[i] = dis(gen);
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Random number generation", duration);

    // Print elements
    printElements(arr, SIZE, "Raw Array");

    // Calculate sum
    start = chrono::high_resolution_clock::now();
    long long sum = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        sum += arr[i];
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Sum calculation", duration);
    cout << "Sum: " << sum << endl;

    // Calculate average
    start = chrono::high_resolution_clock::now();
    double average = static_cast<double>(sum) / SIZE;
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Average calculation", duration);
    cout << "Average: " << average << endl;

    // Find min and max
    start = chrono::high_resolution_clock::now();
    int min_val = arr[0], max_val = arr[0];
    for (size_t i = 1; i < SIZE; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Min/Max finding", duration);
    cout << "Min: " << min_val << ", Max: " << max_val << endl;

    // Sort in descending order
    start = chrono::high_resolution_clock::now();
    sort(arr, arr + SIZE, greater<int>());
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Sorting (descending)", duration);

    // Clean up
    delete[] arr;
}

// Function to perform operations on vector
void analyzeVector(const size_t SIZE, const int MIN_VAL, const int MAX_VAL) {
    cout << "\n=== Vector Analysis ===\n";
    
    // Create and reserve vector
    auto start = chrono::high_resolution_clock::now();
    vector<int> vec;
    vec.reserve(SIZE);  // Pre-allocate memory
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    printExecutionTime("Memory allocation (reserve)", duration);

    // Generate random numbers
    start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(MIN_VAL, MAX_VAL);
    for (size_t i = 0; i < SIZE; ++i) {
        vec.push_back(dis(gen));
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Random number generation", duration);

    // Print elements
    printElements(vec, SIZE, "Vector");

    // Calculate sum
    start = chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& num : vec) {
        sum += num;
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Sum calculation", duration);
    cout << "Sum: " << sum << endl;

    // Calculate average
    start = chrono::high_resolution_clock::now();
    double average = static_cast<double>(sum) / vec.size();
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Average calculation", duration);
    cout << "Average: " << average << endl;

    // Find min and max
    start = chrono::high_resolution_clock::now();
    auto [min_it, max_it] = minmax_element(vec.begin(), vec.end());
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Min/Max finding", duration);
    cout << "Min: " << *min_it << ", Max: " << *max_it << endl;

    // Sort in descending order
    start = chrono::high_resolution_clock::now();
    sort(vec.begin(), vec.end(), greater<int>());
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    printExecutionTime("Sorting (descending)", duration);
}

int main() {
    const size_t SIZE = 1000;  // Number of elements
    const int MIN_VAL = 1;     // Minimum value
    const int MAX_VAL = 10000; // Maximum value

    cout << "Performance Analysis of Different Array Implementations\n";
    cout << "===================================================\n";
    cout << "Dataset size: " << SIZE << " integers\n";
    cout << "Range: [" << MIN_VAL << ", " << MAX_VAL << "]\n";

    // Analyze raw array implementation
    analyzeRawArray(SIZE, MIN_VAL, MAX_VAL);

    // Analyze vector implementation
    analyzeVector(SIZE, MIN_VAL, MAX_VAL);

    cout << "\nPerformance Analysis Report:\n";
    cout << "===========================\n";
    cout << "1. Memory Management:\n"
              << "   - Raw arrays require manual memory management (allocation/deallocation)\n"
              << "   - vector handles memory management automatically and can resize dynamically\n\n"
              << "2. Safety:\n"
              << "   - Raw arrays have no bounds checking, which can lead to buffer overflows\n"
              << "   - vector provides bounds checking and is generally safer\n\n"
              << "3. Convenience:\n"
              << "   - vector provides many built-in functions (push_back, size, capacity)\n"
              << "   - Raw arrays require manual implementation of such functionality\n\n"
              << "4. Performance:\n"
              << "   - Raw arrays might have slightly better performance due to less overhead\n"
              << "   - vector's performance is generally very close to raw arrays\n\n"
              << "Recommendation for Large Datasets:\n"
              << "--------------------------------\n"
              << "For large datasets, vector is recommended because:\n"
              << "1. Better memory management with automatic resizing\n"
              << "2. Safety features prevent common programming errors\n"
              << "3. Rich set of built-in functions and algorithms\n"
              << "4. Performance difference is negligible in most cases\n"
              << "5. Exception safety and RAII compliance\n";

    return 0;
}
