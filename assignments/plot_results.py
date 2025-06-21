import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from matplotlib import rcParams

# Set style for better-looking plots
plt.style.use('seaborn-v0_8')
rcParams['figure.figsize'] = (12, 8)
rcParams['font.size'] = 10

def plot_histograms():
    """Plot histograms of generated random numbers"""
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    
    # Plot integer distribution
    try:
        int_data = pd.read_csv('integer_sample.csv')
        ax1.hist(int_data['Value'], bins=50, alpha=0.7, color='skyblue', edgecolor='black')
        ax1.set_title('Distribution of Uniform Integers (1-100)')
        ax1.set_xlabel('Value')
        ax1.set_ylabel('Frequency')
        ax1.grid(True, alpha=0.3)
    except FileNotFoundError:
        ax1.text(0.5, 0.5, 'integer_sample.csv not found', ha='center', va='center', transform=ax1.transAxes)
        ax1.set_title('Integer Distribution (Data Not Available)')
    
    # Plot float distribution
    try:
        float_data = pd.read_csv('float_sample.csv')
        ax2.hist(float_data['Value'], bins=50, alpha=0.7, color='lightcoral', edgecolor='black')
        ax2.set_title('Distribution of Uniform Floats (0.0-1.0)')
        ax2.set_xlabel('Value')
        ax2.set_ylabel('Frequency')
        ax2.grid(True, alpha=0.3)
    except FileNotFoundError:
        ax2.text(0.5, 0.5, 'float_sample.csv not found', ha='center', va='center', transform=ax2.transAxes)
        ax2.set_title('Float Distribution (Data Not Available)')
    
    plt.tight_layout()
    plt.savefig('histograms.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_execution_time():
    """Plot execution time vs n for different methods"""
    try:
        df = pd.read_csv('performance_data.csv')
        
        # Filter out invalid entries
        df = df[df['ExecutionTime(ms)'] >= 0]
        
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
        
        # Integer distribution timing
        int_data = df[df['Distribution'] == 'Integer']
        for method in int_data['Method'].unique():
            method_data = int_data[int_data['Method'] == method]
            ax1.plot(method_data['Size'], method_data['ExecutionTime(ms)'], 
                    marker='o', linewidth=2, markersize=8, label=method)
        
        ax1.set_title('Execution Time vs Size (Integer Distribution)')
        ax1.set_xlabel('Size (n)')
        ax1.set_ylabel('Execution Time (ms)')
        ax1.set_xscale('log')
        ax1.set_yscale('log')
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        
        # Float distribution timing
        float_data = df[df['Distribution'] == 'Float']
        for method in float_data['Method'].unique():
            method_data = float_data[float_data['Method'] == method]
            ax2.plot(method_data['Size'], method_data['ExecutionTime(ms)'], 
                    marker='s', linewidth=2, markersize=8, label=method)
        
        ax2.set_title('Execution Time vs Size (Float Distribution)')
        ax2.set_xlabel('Size (n)')
        ax2.set_ylabel('Execution Time (ms)')
        ax2.set_xscale('log')
        ax2.set_yscale('log')
        ax2.legend()
        ax2.grid(True, alpha=0.3)
        
        plt.tight_layout()
        plt.savefig('execution_time.png', dpi=300, bbox_inches='tight')
        plt.show()
        
    except FileNotFoundError:
        print("performance_data.csv not found. Please run the C++ program first.")

def plot_memory_usage():
    """Plot memory usage vs n for different methods"""
    try:
        df = pd.read_csv('performance_data.csv')
        
        # Filter out invalid entries
        df = df[df['ExecutionTime(ms)'] >= 0]
        
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
        
        # Integer distribution memory
        int_data = df[df['Distribution'] == 'Integer']
        for method in int_data['Method'].unique():
            method_data = int_data[int_data['Method'] == method]
            ax1.plot(method_data['Size'], method_data['MemoryUsage(bytes)'], 
                    marker='o', linewidth=2, markersize=8, label=method)
        
        ax1.set_title('Memory Usage vs Size (Integer Distribution)')
        ax1.set_xlabel('Size (n)')
        ax1.set_ylabel('Memory Usage (bytes)')
        ax1.set_xscale('log')
        ax1.set_yscale('log')
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        
        # Float distribution memory
        float_data = df[df['Distribution'] == 'Float']
        for method in float_data['Method'].unique():
            method_data = float_data[float_data['Method'] == method]
            ax2.plot(method_data['Size'], method_data['MemoryUsage(bytes)'], 
                    marker='s', linewidth=2, markersize=8, label=method)
        
        ax2.set_title('Memory Usage vs Size (Float Distribution)')
        ax2.set_xlabel('Size (n)')
        ax2.set_ylabel('Memory Usage (bytes)')
        ax2.set_xscale('log')
        ax2.set_yscale('log')
        ax2.legend()
        ax2.grid(True, alpha=0.3)
        
        plt.tight_layout()
        plt.savefig('memory_usage.png', dpi=300, bbox_inches='tight')
        plt.show()
        
    except FileNotFoundError:
        print("performance_data.csv not found. Please run the C++ program first.")

def generate_comparison_table():
    """Generate a comparison table of the results"""
    try:
        df = pd.read_csv('performance_data.csv')
        df = df[df['ExecutionTime(ms)'] >= 0]
        
        print("\n" + "="*80)
        print("PERFORMANCE COMPARISON TABLE")
        print("="*80)
        
        # Group by method and distribution, then calculate averages
        summary = df.groupby(['Method', 'Distribution']).agg({
            'ExecutionTime(ms)': ['mean', 'std'],
            'MemoryUsage(bytes)': 'mean'
        }).round(3)
        
        print(summary)
        
        # Find fastest method for each size and distribution
        print("\n" + "="*80)
        print("FASTEST METHOD BY SIZE AND DISTRIBUTION")
        print("="*80)
        
        fastest = df.loc[df.groupby(['Size', 'Distribution'])['ExecutionTime(ms)'].idxmin()]
        fastest = fastest[['Size', 'Distribution', 'Method', 'ExecutionTime(ms)']]
        print(fastest.to_string(index=False))
        
    except FileNotFoundError:
        print("performance_data.csv not found. Please run the C++ program first.")

def create_comprehensive_report():
    """Create a comprehensive analysis report"""
    try:
        df = pd.read_csv('performance_data.csv')
        df = df[df['ExecutionTime(ms)'] >= 0]
        
        print("\n" + "="*80)
        print("COMPREHENSIVE PERFORMANCE ANALYSIS REPORT")
        print("="*80)
        
        # Overall statistics
        print(f"\nTotal tests performed: {len(df)}")
        print(f"Size range tested: {df['Size'].min()} to {df['Size'].max()}")
        print(f"Methods tested: {', '.join(df['Method'].unique())}")
        print(f"Distributions tested: {', '.join(df['Distribution'].unique())}")
        
        # Performance analysis by method
        print("\n" + "-"*50)
        print("PERFORMANCE ANALYSIS BY METHOD")
        print("-"*50)
        
        method_stats = df.groupby('Method').agg({
            'ExecutionTime(ms)': ['mean', 'min', 'max'],
            'MemoryUsage(bytes)': 'mean'
        }).round(3)
        
        print(method_stats)
        
        # Memory efficiency analysis
        print("\n" + "-"*50)
        print("MEMORY EFFICIENCY ANALYSIS")
        print("-"*50)
        
        # Calculate memory efficiency (bytes per element)
        df['MemoryPerElement'] = df['MemoryUsage(bytes)'] / df['Size']
        memory_efficiency = df.groupby(['Method', 'Distribution'])['MemoryPerElement'].mean()
        print(memory_efficiency.round(2))
        
        # Scalability analysis
        print("\n" + "-"*50)
        print("SCALABILITY ANALYSIS")
        print("-"*50)
        
        # Calculate scaling factor (how much slower when size increases 10x)
        scaling_analysis = []
        for method in df['Method'].unique():
            for dist in df['Distribution'].unique():
                method_dist_data = df[(df['Method'] == method) & (df['Distribution'] == dist)]
                if len(method_dist_data) >= 2:
                    sizes = sorted(method_dist_data['Size'].unique())
                    times = [method_dist_data[method_dist_data['Size'] == size]['ExecutionTime(ms)'].iloc[0] 
                            for size in sizes]
                    
                    if len(times) >= 2:
                        scaling_factor = times[-1] / times[0]  # Time increase from smallest to largest
                        size_factor = sizes[-1] / sizes[0]     # Size increase from smallest to largest
                        scaling_analysis.append({
                            'Method': method,
                            'Distribution': dist,
                            'Size_Increase': f"{size_factor:.0f}x",
                            'Time_Increase': f"{scaling_factor:.2f}x",
                            'Efficiency': f"{size_factor/scaling_factor:.2f}"
                        })
        
        scaling_df = pd.DataFrame(scaling_analysis)
        print(scaling_df.to_string(index=False))
        
    except FileNotFoundError:
        print("performance_data.csv not found. Please run the C++ program first.")

if __name__ == "__main__":
    print("Random Number Generator Performance Analysis - Plotting Script")
    print("="*60)
    
    # Generate all plots and analysis
    plot_histograms()
    plot_execution_time()
    plot_memory_usage()
    generate_comparison_table()
    create_comprehensive_report()
    
    print("\n" + "="*60)
    print("ANALYSIS COMPLETE")
    print("="*60)
    print("Generated files:")
    print("- histograms.png: Distribution histograms")
    print("- execution_time.png: Execution time comparisons")
    print("- memory_usage.png: Memory usage comparisons")
    print("\nUse these plots and the analysis above for your report.") 