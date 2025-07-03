# VaxNet: Real-World Network Vaccination Game

A Python-based simulation game that models disease spread over real human interaction networks and challenges players to develop effective vaccination strategies.

## 🎮 Game Overview

VaxNet simulates the spread of infectious diseases through social networks using the SIR (Susceptible-Infected-Recovered) model. Players must strategically vaccinate individuals to minimize both infection spread and total cost.

### Key Features

- **Real Network Models**: Multiple network types including Barabasi-Albert, Erdos-Renyi, and Watts-Strogatz
- **SIR Disease Dynamics**: Realistic disease spread simulation
- **Multiple Vaccination Strategies**: Random, Ring, High-Density, and Greedy approaches
- **Interactive Gameplay**: Manual node selection or automatic strategy execution
- **Visual Network Representation**: Real-time network visualization with color-coded states
- **Scoring System**: Cost-based scoring with Gold/Silver/Bronze rankings

## 🚀 Quick Start

### Prerequisites

- Python 3.7 or higher
- Required packages (install via `pip install -r requirements.txt`)

### Installation

1. Clone or download the project
2. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Run the game:
   ```bash
   python vaxnet_game.py
   ```

## 🎯 How to Play

### Game Setup

1. Choose a network type:

   - **Synthetic Barabasi-Albert**: Scale-free network (default)
   - **Erdos-Renyi**: Random network
   - **Watts-Strogatz**: Small-world network

2. Choose network size:

   - Number of nodes (20-500, default=100)
   - Larger networks = more complex gameplay
   - Smaller networks = faster gameplay and better visualization

3. Configure game parameters:
   - Initial infection rate (1-20%)
   - Infection probability (10-50%)
   - Recovery time (1-5 rounds)
   - Vaccination cost ($10-100)
   - Infection penalty ($50-200)
   - Max vaccinations per turn (1-5)

### Gameplay

Each round consists of:

1. **View Current State**: See network statistics and costs
2. **Choose Vaccination Strategy**:
   - **Manual**: Enter node numbers to vaccinate
   - **Auto**: Use predefined strategies
   - **Skip**: Pass without vaccinating
3. **Watch Disease Spread**: See new infections and recoveries
4. **Optional Visualization**: View network graph

### Vaccination Strategies

#### 1. Random Vaccination

- **How it works**: Vaccinate random susceptible individuals
- **Pros**: Simple to implement
- **Cons**: May miss critical spread points

#### 2. Ring Vaccination

- **How it works**: Vaccinate susceptible individuals around infected ones
- **Pros**: Targets high-risk areas
- **Cons**: Requires knowledge of nearby infections

#### 3. High-Density Targeting

- **How it works**: Vaccinate areas with many connections (high degree nodes)
- **Pros**: Prevents rapid spread in crowded zones
- **Cons**: May ignore isolated infections

#### 4. Greedy Strategy

- **How it works**: Vaccinate susceptible individuals with the most infected neighbors
- **Pros**: Very efficient at blocking spread
- **Cons**: Requires checking every node each turn

### Game Commands

- **Node Selection**: Enter numbers separated by spaces (e.g., `23 41`)
- **Auto Strategy**: Type `auto` then choose strategy
- **Skip Turn**: Type `skip`
- **Visualization**: Answer `y` when prompted

### Victory Conditions

- **Goal**: Eradicate the disease (no infected nodes remain)
- **Scoring**: Lower total cost = better performance
- **Ranks**:
  - **GOLD**: < $1000
  - **SILVER**: $1000-$2000
  - **BRONZE**: $2000-$3000
  - **NEEDS IMPROVEMENT**: > $3000

## 🔬 Technical Details

### SIR Model Implementation

The game uses a discrete-time SIR model:

- **S (Susceptible)**: Can catch the disease
- **I (Infected)**: Currently has and spreads the disease
- **R (Recovered)**: Had the disease, now immune
- **V (Vaccinated)**: Protected from infection

### Infection Dynamics

- Infection probability increases with the number of infected neighbors
- Formula: `P(infection) = 1 - (1 - p)^n` where `p` is base probability and `n` is infected neighbors
- Recovery occurs after a fixed number of rounds
- Vaccinated nodes are permanently protected

### Network Types

1. **Barabasi-Albert (Scale-free)**:

   - Models real-world networks with power-law degree distribution
   - Some nodes have many connections (hubs)
   - Good for modeling social networks

2. **Erdos-Renyi (Random)**:

   - Each pair of nodes connected with fixed probability
   - Homogeneous degree distribution
   - Good baseline for comparison

3. **Watts-Strogatz (Small-world)**:
   - High clustering with short path lengths
   - Models networks like friendship circles
   - Disease can spread quickly through shortcuts

## 📊 Sample Game Output

```
============================================================
ROUND 4
============================================================
Susceptible: 45 | Infected: 12 | Recovered: 38 | Vaccinated: 5
Total Cost: $650 | Vaccinations Used: 5 | Infections: 6
Current Rank: SILVER
============================================================

Choose up to 2 nodes to vaccinate:
Enter node numbers separated by spaces, or 'auto' for automatic strategy
Available strategies: random, ring, density, greedy
> 23 41
Vaccinated node 23
Vaccinated node 41
New infections: 6
Recovered this round: 10
```

## 🛠️ Customization

### Adding New Networks

To add real-world network data:

1. Download network data from sources like:

   - [SNAP Datasets](https://snap.stanford.edu/data/)
   - [Network Repository](https://networkrepository.com/)
   - [Cambridge Network Data](https://www.cnn.group.cam.ac.uk/Resources/resources)

2. Modify the `load_network_data()` method to load your data

3. Use NetworkX functions like `nx.read_edgelist()` or `nx.read_adjlist()`

### Modifying Parameters

Edit the game parameters in the `__init__()` method:

```python
self.vaccination_cost = 50      # Cost per vaccination
self.infection_penalty = 100    # Cost per infection
self.infection_probability = 0.3 # Base infection probability
self.recovery_time = 3          # Rounds until recovery
```

### Adding New Strategies

Implement new vaccination strategies by adding methods to the `VaxNetGame` class and updating the `auto_vaccinate()` method.

## 📚 Educational Value

This game demonstrates:

- **Network Science**: How diseases spread through social networks
- **Epidemiology**: SIR model and vaccination strategies
- **Algorithm Design**: Different approaches to optimization problems
- **Data Visualization**: Network graphs and statistical displays
- **Public Health**: Real-world implications of vaccination strategies

## 🤝 Contributing

Feel free to contribute by:

- Adding new network datasets
- Implementing additional vaccination strategies
- Improving the visualization
- Adding new game modes
- Enhancing the scoring system

## 📄 License

This project is open source and available under the MIT License.

## 🙏 Acknowledgments

- NetworkX library for network analysis
- Matplotlib for visualization
- SIR model from epidemiology literature
- Real-world network datasets from various research groups

---

**Happy Vaccinating! 🩹💉**
