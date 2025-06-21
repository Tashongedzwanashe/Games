# Random Number Generator Performance Analysis

This project implements a comprehensive C++ program to analyze the performance of different storage methods for generating random numbers, along with Python scripts for data visualization and analysis.

## Features

- **Four Storage Methods**: Static array, Dynamic array, std::vector, Manual allocation
- **Two Distributions**: Uniform integers (1-100) and Uniform floats (0.0-1.0)
- **Three Sizes**: n = 1,000, 10,000, 100,000
- **Performance Metrics**: Execution time and memory usage measurement
- **Data Export**: CSV files for external analysis
- **Visualization**: Python scripts for plotting results

## Files

- `ass2_rand_num_gen.cpp` - Main C++ program
- `plot_results.py` - Python analysis and plotting script
- `analysis_report.md` - Comprehensive analysis report template
- `Makefile` - Build automation
- `README.md` - This file

## Requirements

### C++ Requirements

- C++17 compatible compiler (g++, clang++, MSVC)
- Standard C++ libraries

### Python Requirements (for analysis)

- Python 3.6+
- pandas
- matplotlib
- numpy
- seaborn

## Quick Start

### 1. Compile the Program

```bash
# Using Makefile (recommended)
make

# Or manually
g++ -std=c++17 -O2 -Wall -Wextra -o ass2_rand_num_gen ass2_rand_num_gen.cpp
```

### 2. Run the Program

```bash
# Using Makefile
make run

# Or manually
./ass2_rand_num_gen
```

### 3. Install Python Dependencies

```bash
# Using Makefile
make install-deps

# Or manually
pip install pandas matplotlib numpy seaborn
```

### 4. Generate Analysis and Plots

```bash
# Using Makefile (runs program and generates plots)
make analyze

# Or manually
python plot_results.py
```

## Output Files

After running the program, you'll get:

### CSV Data Files

- `performance_data.csv` - Performance metrics for all tests
- `integer_sample.csv` - Sample integer data for histogram
- `float_sample.csv` - Sample float data for histogram

### Generated Plots

- `histograms.png` - Distribution histograms
- `execution_time.png` - Execution time comparisons
- `memory_usage.png` - Memory usage comparisons

## Program Output

The C++ program will display:

- Real-time performance measurements
- Memory usage statistics
- Progress indicators for each test
- Summary of generated files

## Analysis Features

The Python script provides:

### 1. Distribution Analysis

- Histograms of generated random numbers
- Visual verification of uniformity
- Comparison between integer and float distributions

### 2. Performance Analysis

- Execution time vs. data size plots
- Memory usage vs. data size plots
- Method comparison tables
- Scalability analysis

### 3. Statistical Summary

- Performance rankings
- Memory efficiency analysis
- Scaling characteristics
- Comprehensive comparison tables

## Storage Methods Explained

### 1. Static Array

- Fixed-size array allocation
- Limited to n ≤ 1,000
- Fastest for small sizes
- No dynamic memory allocation

### 2. Dynamic Array

- Using `new[]` and `delete[]`
- Manual memory management
- Good performance
- Risk of memory leaks if not handled properly

### 3. std::vector

- Standard C++ container
- Automatic memory management
- Consistent performance
- Recommended for most applications

### 4. Manual Allocation

- Using `malloc()` and `free()`
- C-style memory management
- Similar performance to dynamic array
- Used for C library compatibility

## Customization

### Modifying Test Parameters

Edit the main function in `ass2_rand_num_gen.cpp`:

```cpp
// Test sizes
std::vector<int> sizes = {1000, 10000, 100000};

// Add more sizes
std::vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
```

### Adding New Distributions

Add new distribution functions:

```cpp
template<typename T>
void generate_normal_distribution(T* data, int n, std::mt19937& gen) {
    std::normal_distribution<T> dist(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        data[i] = dist(gen);
    }
}
```

### Modifying Plot Styles

Edit `plot_results.py` to customize:

- Plot colors and styles
- Figure sizes
- Output formats
- Analysis metrics

## Troubleshooting

### Compilation Issues

- Ensure C++17 support: `g++ --version`
- Check compiler flags in Makefile
- Verify all required headers are included

### Python Issues

- Install dependencies: `pip install -r requirements.txt`
- Check Python version: `python --version`
- Ensure matplotlib backend is available

### Runtime Issues

- Check available memory for large n values
- Verify file write permissions
- Monitor system resources during execution

## Performance Tips

### For Best Results

1. Run on a dedicated machine (minimize background processes)
2. Use release builds with optimization (`-O2` or `-O3`)
3. Run multiple times and average results
4. Consider system-specific optimizations

### Memory Considerations

- Large n values (100,000+) require significant memory
- Monitor system memory usage
- Consider running on systems with sufficient RAM

## Contributing

To extend this project:

1. Add new storage methods
2. Implement additional distributions
3. Enhance visualization capabilities
4. Add statistical analysis features
5. Improve performance measurement accuracy

## License

This project is provided as educational material. Feel free to modify and extend for your needs.

## Support

For issues or questions:

1. Check the troubleshooting section
2. Review the code comments
3. Verify your system meets requirements
4. Test with smaller n values first

---

**Note**: Results may vary depending on your system specifications, compiler optimizations, and system load. For reproducible results, run on a dedicated system with minimal background processes.
