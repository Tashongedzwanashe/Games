# Contain the Spread - Vaccination Strategy Game

A C++ simulation game that models disease spread using SIR (Susceptible-Infected-Recovered) dynamics, where players must strategically vaccinate individuals to minimize the total cost of vaccinations and infections.

## 🎮 Game Overview

The game simulates a disease spreading across a 2D grid of individuals. Players can vaccinate susceptible individuals each turn to prevent infection, but vaccinations come at a cost. The goal is to minimize the combined cost of vaccinations and infections.

### SIR Dynamics

- **S (Susceptible)**: Can catch the disease
- **I (Infected)**: Currently has and spreads the disease
- **R (Recovered)**: Had the disease, now immune
- **V (Vaccinated)**: Protected from infection

## 🚀 Features

### Core Gameplay

- **Configurable Grid Size**: From small 10x10 to large 1000x1000 grids
- **SIR Disease Model**: Realistic disease spread simulation
- **Cost Management**: Balance vaccination costs vs. infection penalties
- **Multiple Strategies**: Choose from 5 different vaccination approaches

### Vaccination Strategies

1. **Manual Strategy**

   - Player manually selects which cells to vaccinate
   - Full control over vaccination decisions
   - Best for learning and understanding the game

2. **Random Strategy**

   - Vaccinates random susceptible individuals
   - Simple but may miss critical infection hotspots
   - Good baseline for comparison

3. **Ring Vaccination**

   - Targets susceptible individuals around infected ones
   - Creates a protective barrier around infection clusters
   - Effective for containing localized outbreaks

4. **High-Density Targeting**

   - Vaccinates areas with many people close together
   - Prevents rapid spread in crowded zones
   - Good for urban-like scenarios

5. **Greedy Strategy**
   - Vaccinates susceptible individuals with the most infected neighbors
   - Most efficient at blocking disease spread
   - Requires checking every cell each turn

## 📋 Requirements

- **Compiler**: GCC/G++ with C++11 support
- **OS**: Windows, Linux, or macOS
- **Dependencies**: None (standard library only)

## 🔧 Compilation

### Windows

```bash
# Using batch file
compile.bat

# Or manually
g++ -std=c++11 -Wall -Wextra -O2 -o contain_the_spread.exe contain_the_spread.cpp
```

### Linux/macOS

```bash
# Using Makefile
make

# Or manually
g++ -std=c++11 -Wall -Wextra -O2 -o contain_the_spread contain_the_spread.cpp
```

## 🎯 How to Play

1. **Configure Simulation**

   - Set grid dimensions (e.g., 20x20 for testing, 100x100 for challenge)
   - Choose initial infection rate (1-10% recommended)
   - Set infection probability (≥0.125 for 8-neighbor spread)
   - Configure costs and recovery time

2. **Choose Strategy**

   - Select from 5 vaccination strategies
   - Each strategy has different strengths and weaknesses

3. **Play the Game**

   - Watch the disease spread across the grid
   - Vaccinate strategically to contain outbreaks
   - Monitor costs and infection counts
   - Continue until disease is eradicated

4. **Achieve Victory**
   - Eradicate all infections
   - Minimize total cost
   - Earn Gold/Silver/Bronze ranking

## 🎮 Sample Gameplay

```
=== CONTAIN THE SPREAD - Vaccination Strategy Game ===
Turn: 5
Grid Size: 20x20
Infected: 12 | Vaccinated: 6 | Recovered: 8
Total Cost: $360 (Vaccinations: $60 + Infections: $300)

S S I S S V S S S S
S S S S S S S S S S
I S S V S S S S S S
S S S S S I S S S S
...

Enter cells to vaccinate (format: x y, e.g., "3 2"). Enter 'done' to finish:
> 1 1
> 2 2
> done
--- Infection Spreading ---
```

## 📊 Scoring System

```
Total Cost = (Vaccinated Count × Vaccination Cost) + (Infected Count × Infection Penalty)
```

### Ranking System

- **Gold**: Total Cost < $1000
- **Silver**: Total Cost < $2000
- **Bronze**: Total Cost < $3000
- **Needs Improvement**: Total Cost ≥ $3000

## 🎯 Strategy Tips

### For Beginners

- Start with small grids (10x10) and manual strategy
- Use low infection rates (1-2%) to learn the mechanics
- Focus on creating vaccination barriers around infected areas

### For Advanced Players

- Experiment with different strategies on larger grids
- Analyze the trade-off between vaccination cost and infection penalty
- Use the greedy strategy for optimal containment
- Try different infection probabilities to see how they affect spread

### Parameter Recommendations

- **Small Grid (10x20)**: Good for learning and testing strategies
- **Medium Grid (50x50)**: Balanced challenge and performance
- **Large Grid (100x100)**: Advanced simulation with complex dynamics
- **Infection Probability**: 0.15-0.25 for realistic spread patterns
- **Recovery Time**: 2-3 turns for manageable game length

## 🔬 Educational Value

This game demonstrates:

- **Epidemiological Modeling**: SIR dynamics and disease spread
- **Resource Management**: Balancing costs and benefits
- **Strategic Thinking**: Planning and optimization
- **Data Analysis**: Tracking statistics and performance
- **Algorithm Design**: Different vaccination strategies

## 🛠️ Technical Details

### Code Structure

- **Object-Oriented Design**: Clean separation of game logic
- **Modular Architecture**: Easy to extend with new features
- **Efficient Algorithms**: Optimized for large grid simulations
- **Cross-Platform**: Works on Windows, Linux, and macOS

### Performance

- **Memory Efficient**: Uses 2D vectors for grid representation
- **Fast Execution**: Optimized compilation with -O2 flag
- **Scalable**: Handles grids up to 1000x1000 efficiently

## 🚀 Future Extensions

Potential enhancements for advanced versions:

- **Graphical Interface**: SFML or SDL2 visualization
- **Multiple Virus Strains**: Different infection properties
- **Movement Simulation**: Individuals moving across the grid
- **Contact Tracing**: Advanced infection tracking
- **Network Effects**: Social network-based spread
- **Vaccine Efficacy**: Different vaccine types and effectiveness

## 📝 License

This project is open source and available for educational use.

## 🤝 Contributing

Feel free to contribute improvements, bug fixes, or new features!

---

**Enjoy playing "Contain the Spread" and learning about epidemiological modeling!** 🦠💉
