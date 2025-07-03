#!/usr/bin/env python3
"""
Ahmad Tomeh 100001925
Emmanuel Mufunde 100001936
George Kilibwa 100002924

03.07.2025 (1530pm) 

A Real-World Network Vaccination Game Using Empirical Contact Data

This game simulates disease spread over real human interaction networks
and allows players to vaccinate nodes to minimize infection and cost.
"""

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random
import time
from typing import Dict, List, Tuple, Optional
import os
import urllib.request
import zipfile
import io

class VaxNetGame:
    def __init__(self):
        self.G = None
        self.status = {}  # S, I, R, V for each node
        self.infection_time = {}  # Track how long each node has been infected
        self.vaccination_cost = 50
        self.infection_penalty = 100
        self.infection_probability = 0.3
        self.recovery_time = 3
        self.max_vaccinations_per_turn = 2
        self.total_cost = 0
        self.vaccinations_used = 0
        self.infections_occurred = 0
        self.round_number = 0
        
    def load_network_data(self, network_type: str = "synthetic", num_nodes: int = 100) -> None:
        """Load network data from various sources"""
        if network_type == "synthetic":
            # Create a synthetic network for demonstration
            self.G = nx.barabasi_albert_graph(num_nodes, 3, seed=42)
            print(f"Loaded synthetic Barabasi-Albert network with {num_nodes} nodes")
        elif network_type == "erdos_renyi":
            # Adjust edge probability based on number of nodes for reasonable connectivity
            edge_prob = min(0.1, 10.0 / num_nodes)  # Ensure reasonable connectivity
            self.G = nx.erdos_renyi_graph(num_nodes, edge_prob, seed=42)
            print(f"Loaded Erdos-Renyi random network with {num_nodes} nodes")
        elif network_type == "watts_strogatz":
            # Adjust k (neighbors) based on network size
            k = min(4, num_nodes // 10)  # Ensure k doesn't exceed half the nodes
            self.G = nx.watts_strogatz_graph(num_nodes, k, 0.3, seed=42)
            print(f"Loaded Watts-Strogatz small-world network with {num_nodes} nodes")
        else:
            # Default to synthetic
            self.G = nx.barabasi_albert_graph(num_nodes, 3, seed=42)
            print(f"Loaded synthetic Barabasi-Albert network with {num_nodes} nodes")
    
    def initialize_game(self, initial_infection_rate: float = 0.05) -> None:
        """Initialize the game state"""
        if self.G is None:
            self.load_network_data("synthetic", 100)
        
        # Initialize all nodes as susceptible
        for node in self.G.nodes():
            self.status[node] = 'S'
            self.infection_time[node] = 0
        
        # Randomly infect some nodes
        num_nodes = len(self.G.nodes())
        num_infected = int(num_nodes * initial_infection_rate)
        infected_nodes = random.sample(list(self.G.nodes()), num_infected)
        
        for node in infected_nodes:
            self.status[node] = 'I'
            self.infection_time[node] = 0
        
        self.total_cost = 0
        self.vaccinations_used = 0
        self.infections_occurred = 0
        self.round_number = 0
        
        print(f"Game initialized with {num_infected} initially infected nodes")
    
    def get_neighbors(self, node: int) -> List[int]:
        """Get all neighbors of a node"""
        return list(self.G.neighbors(node))
    
    def count_infected_neighbors(self, node: int) -> int:
        """Count how many neighbors of a node are infected"""
        neighbors = self.get_neighbors(node)
        return sum(1 for neighbor in neighbors if self.status[neighbor] == 'I')
    
    def vaccinate_node(self, node: int) -> bool:
        """Vaccinate a specific node"""
        if self.status[node] == 'S':
            self.status[node] = 'V'
            self.total_cost += self.vaccination_cost
            self.vaccinations_used += 1
            return True
        return False
    
    def spread_infection(self) -> int:
        """Simulate one step of infection spread using SIR dynamics"""
        new_infections = 0
        nodes_to_infect = []
        
        # Find susceptible nodes that might get infected
        for node in self.G.nodes():
            if self.status[node] == 'S':
                infected_neighbors = self.count_infected_neighbors(node)
                if infected_neighbors > 0:
                    # Probability of infection increases with number of infected neighbors
                    infection_chance = 1 - (1 - self.infection_probability) ** infected_neighbors
                    if random.random() < infection_chance:
                        nodes_to_infect.append(node)
        
        # Apply infections
        for node in nodes_to_infect:
            self.status[node] = 'I'
            self.infection_time[node] = 0
            new_infections += 1
            self.infections_occurred += 1
            self.total_cost += self.infection_penalty
        
        return new_infections
    
    def update_recoveries(self) -> int:
        """Update recovery status of infected nodes"""
        recovered_this_round = 0
        
        for node in self.G.nodes():
            if self.status[node] == 'I':
                self.infection_time[node] += 1
                if self.infection_time[node] >= self.recovery_time:
                    self.status[node] = 'R'
                    recovered_this_round += 1
        
        return recovered_this_round
    
    def get_game_stats(self) -> Dict:
        """Get current game statistics"""
        stats = {}
        for status in ['S', 'I', 'R', 'V']:
            stats[status] = sum(1 for node_status in self.status.values() if node_status == status)
        return stats
    
    def is_game_over(self) -> bool:
        """Check if the game is over (no more infected nodes)"""
        return self.get_game_stats()['I'] == 0
    
    def get_score(self) -> int:
        """Calculate current score (lower is better)"""
        return self.total_cost
    
    def get_rank(self) -> str:
        """Get rank based on total cost"""
        score = self.get_score()
        if score < 1000:
            return "GOLD"
        elif score < 2000:
            return "SILVER"
        elif score < 3000:
            return "BRONZE"
        else:
            return "NEEDS IMPROVEMENT"
    
    def random_vaccination_strategy(self) -> List[int]:
        """Random vaccination strategy"""
        susceptible_nodes = [node for node in self.G.nodes() if self.status[node] == 'S']
        if not susceptible_nodes:
            return []
        
        num_to_vaccinate = min(self.max_vaccinations_per_turn, len(susceptible_nodes))
        return random.sample(susceptible_nodes, num_to_vaccinate)
    
    def ring_vaccination_strategy(self) -> List[int]:
        """Ring vaccination strategy - vaccinate around infected nodes"""
        candidates = set()
        
        # Find susceptible neighbors of infected nodes
        for node in self.G.nodes():
            if self.status[node] == 'I':
                neighbors = self.get_neighbors(node)
                for neighbor in neighbors:
                    if self.status[neighbor] == 'S':
                        candidates.add(neighbor)
        
        candidates = list(candidates)
        num_to_vaccinate = min(self.max_vaccinations_per_turn, len(candidates))
        return random.sample(candidates, num_to_vaccinate) if candidates else []
    
    def high_density_strategy(self) -> List[int]:
        """High-density targeting strategy"""
        susceptible_nodes = [node for node in self.G.nodes() if self.status[node] == 'S']
        if not susceptible_nodes:
            return []
        
        # Calculate degree for each susceptible node
        node_degrees = [(node, self.G.degree(node)) for node in susceptible_nodes]
        # Sort by degree (highest first)
        node_degrees.sort(key=lambda x: x[1], reverse=True)
        
        num_to_vaccinate = min(self.max_vaccinations_per_turn, len(node_degrees))
        return [node for node, _ in node_degrees[:num_to_vaccinate]]
    
    def greedy_strategy(self) -> List[int]:
        """Greedy strategy - vaccinate nodes with most infected neighbors"""
        susceptible_nodes = [node for node in self.G.nodes() if self.status[node] == 'S']
        if not susceptible_nodes:
            return []
        
        # Calculate infected neighbors for each susceptible node
        node_infected_neighbors = [(node, self.count_infected_neighbors(node)) 
                                  for node in susceptible_nodes]
        # Sort by number of infected neighbors (highest first)
        node_infected_neighbors.sort(key=lambda x: x[1], reverse=True)
        
        num_to_vaccinate = min(self.max_vaccinations_per_turn, len(node_infected_neighbors))
        return [node for node, _ in node_infected_neighbors[:num_to_vaccinate]]
    
    def auto_vaccinate(self, strategy: str) -> List[int]:
        """Apply automatic vaccination strategy"""
        if strategy == "random":
            return self.random_vaccination_strategy()
        elif strategy == "ring":
            return self.ring_vaccination_strategy()
        elif strategy == "density":
            return self.high_density_strategy()
        elif strategy == "greedy":
            return self.greedy_strategy()
        else:
            return []
    
    def visualize_network(self, save_plot: bool = False) -> None:
        """Visualize the current network state"""
        if self.G is None:
            print("No network loaded!")
            return
        
        plt.figure(figsize=(12, 8))
        
        # Define colors for different states
        colors = {'S': 'lightgray', 'I': 'red', 'R': 'green', 'V': 'blue'}
        node_colors = [colors[self.status[node]] for node in self.G.nodes()]
        
        # Position nodes using spring layout
        pos = nx.spring_layout(self.G, seed=42)
        
        # Draw the network
        nx.draw(self.G, pos, node_color=node_colors, node_size=300, 
                with_labels=True, font_size=8, font_weight='bold',
                edge_color='gray', alpha=0.7)
        
        # Add legend
        legend_elements = [plt.Line2D([0], [0], marker='o', color='w', 
                                     markerfacecolor=color, markersize=10, label=state)
                          for state, color in colors.items()]
        plt.legend(handles=legend_elements, loc='upper left')
        
        # Add title with current stats
        stats = self.get_game_stats()
        title = f"Round {self.round_number} - S:{stats['S']} I:{stats['I']} R:{stats['R']} V:{stats['V']} - Cost: {self.total_cost}"
        plt.title(title, fontsize=14, fontweight='bold')
        
        if save_plot:
            plt.savefig(f'vaxnet_round_{self.round_number}.png', dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def print_game_state(self) -> None:
        """Print current game state to console"""
        stats = self.get_game_stats()
        print(f"\n{'='*60}")
        print(f"ROUND {self.round_number}")
        print(f"{'='*60}")
        print(f"Susceptible: {stats['S']} | Infected: {stats['I']} | Recovered: {stats['R']} | Vaccinated: {stats['V']}")
        print(f"Total Cost: ${self.total_cost} | Vaccinations Used: {self.vaccinations_used} | Infections: {self.infections_occurred}")
        print(f"Current Rank: {self.get_rank()}")
        print(f"{'='*60}")
    
    def get_user_vaccination_choice(self) -> List[int]:
        """Get vaccination choices from user"""
        print(f"\nChoose up to {self.max_vaccinations_per_turn} nodes to vaccinate:")
        print("Enter node numbers separated by spaces, or 'auto' for automatic strategy")
        print("Available strategies: random, ring, density, greedy")
        
        while True:
            try:
                choice = input("> ").strip().lower()
                
                if choice == "auto":
                    print("Available strategies: random, ring, density, greedy")
                    strategy = input("Enter strategy: ").strip().lower()
                    nodes = self.auto_vaccinate(strategy)
                    if nodes:
                        print(f"Auto-strategy '{strategy}' selected {len(nodes)} nodes: {nodes}")
                    else:
                        print(f"Auto-strategy '{strategy}' found no suitable nodes to vaccinate")
                    return nodes
                
                elif choice == "skip":
                    return []
                
                else:
                    # Parse node numbers
                    node_numbers = [int(x) for x in choice.split()]
                    
                    # Validate nodes
                    valid_nodes = []
                    for node in node_numbers:
                        if node in self.G.nodes():
                            if self.status[node] == 'S':
                                valid_nodes.append(node)
                            else:
                                print(f"Node {node} is not susceptible (status: {self.status[node]})")
                        else:
                            print(f"Node {node} does not exist")
                    
                    if len(valid_nodes) <= self.max_vaccinations_per_turn:
                        return valid_nodes
                    else:
                        print(f"Too many nodes selected. Maximum allowed: {self.max_vaccinations_per_turn}")
                        
            except ValueError:
                print("Invalid input. Please enter numbers separated by spaces, 'auto', or 'skip'")
            except KeyboardInterrupt:
                print("\nGame interrupted by user")
                return []
    
    def play_round(self) -> bool:
        """Play one round of the game"""
        self.round_number += 1
        
        # Print current state
        self.print_game_state()
        
        # Check if game is over
        if self.is_game_over():
            print("\n🎉 DISEASE ERADICATED! 🎉")
            print(f"Final Score: ${self.total_cost}")
            print(f"Final Rank: {self.get_rank()}")
            return False
        
        # Get vaccination choices
        nodes_to_vaccinate = self.get_user_vaccination_choice()
        
        # Apply vaccinations (only print if nodes were manually selected)
        if nodes_to_vaccinate:
            print(f"Vaccinating {len(nodes_to_vaccinate)} nodes...")
            for node in nodes_to_vaccinate:
                if self.vaccinate_node(node):
                    print(f"  ✓ Vaccinated node {node}")
                else:
                    print(f"  ✗ Failed to vaccinate node {node}")
        else:
            print("No vaccinations this round")
        
        # Spread infection
        new_infections = self.spread_infection()
        if new_infections > 0:
            print(f"New infections: {new_infections}")
        
        # Update recoveries
        recovered = self.update_recoveries()
        if recovered > 0:
            print(f"Recovered this round: {recovered}")
        
        # Optional: visualize network
        visualize = input("\nVisualize network? (y/n): ").strip().lower()
        if visualize == 'y':
            self.visualize_network()
        
        return True
    
    def run_game(self) -> None:
        """Run the complete game"""
        print("🎮 VAXNET: Real-World Network Vaccination Game 🎮")
        print("=" * 60)
        
        # Game setup
        print("\nGame Setup:")
        print("1. Synthetic Barabasi-Albert network")
        print("2. Erdos-Renyi random network") 
        print("3. Watts-Strogatz small-world network")
        
        network_choice = input("Choose network type (1-3, default=1): ").strip()
        network_types = {"1": "synthetic", "2": "erdos_renyi", "3": "watts_strogatz"}
        network_type = network_types.get(network_choice, "synthetic")
        
        # Get number of nodes
        try:
            num_nodes = int(input("Number of nodes (20-500, default=100): ") or "100")
            num_nodes = max(20, min(500, num_nodes))  # Clamp between 20 and 500
        except ValueError:
            print("Invalid input. Using default of 100 nodes.")
            num_nodes = 100
        
        self.load_network_data(network_type, num_nodes)
        
        # Get game parameters
        try:
            infection_rate = float(input("Initial infection rate (0.01-0.2, default=0.05): ") or "0.05")
            infection_prob = float(input("Infection probability (0.1-0.5, default=0.3): ") or "0.3")
            recovery_time = int(input("Recovery time (1-5, default=3): ") or "3")
            vacc_cost = int(input("Vaccination cost (10-100, default=50): ") or "50")
            infection_penalty = int(input("Infection penalty (50-200, default=100): ") or "100")
            max_vacc = int(input("Max vaccinations per turn (1-5, default=2): ") or "2")
        except ValueError:
            print("Using default values due to invalid input")
            infection_rate, infection_prob, recovery_time = 0.05, 0.3, 3
            vacc_cost, infection_penalty, max_vacc = 50, 100, 2
        
        # Set parameters
        self.infection_probability = infection_prob
        self.recovery_time = recovery_time
        self.vaccination_cost = vacc_cost
        self.infection_penalty = infection_penalty
        self.max_vaccinations_per_turn = max_vacc
        
        # Initialize game
        self.initialize_game(infection_rate)
        
        print(f"\nGame initialized with {len(self.G.nodes())} nodes!")
        print("Goal: Eradicate the disease while minimizing total cost")
        print("Commands: Enter node numbers to vaccinate, 'auto' for automatic strategy, 'skip' to pass")
        
        # Main game loop
        while self.play_round():
            continue
        
        print("\n🏁 GAME OVER 🏁")
        print(f"Final Statistics:")
        print(f"Total Cost: ${self.total_cost}")
        print(f"Vaccinations Used: {self.vaccinations_used}")
        print(f"Total Infections: {self.infections_occurred}")
        print(f"Final Rank: {self.get_rank()}")


def main():
    """Main function to run the game"""
    try:
        game = VaxNetGame()
        game.run_game()
    except KeyboardInterrupt:
        print("\n\nGame interrupted by user. Thanks for playing!")
    except Exception as e:
        print(f"\nAn error occurred: {e}")
        print("Please check your input and try again.")


if __name__ == "__main__":
    main() 