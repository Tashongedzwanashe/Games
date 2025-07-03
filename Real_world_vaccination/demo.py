#!/usr/bin/env python3
"""
Demo script for VaxNet game showing automated gameplay with different strategies
"""

from vaxnet_game import VaxNetGame
import time

def run_automated_game(strategy_name: str, network_type: str = "synthetic", 
                      num_nodes: int = 100, max_rounds: int = 20) -> dict:
    """Run an automated game with a specific strategy"""
    print(f"\n{'='*60}")
    print(f"Running automated game with {strategy_name.upper()} strategy")
    print(f"Network type: {network_type} with {num_nodes} nodes")
    print(f"{'='*60}")
    
    game = VaxNetGame()
    game.load_network_data(network_type, num_nodes)
    game.initialize_game(initial_infection_rate=0.1)
    
    # Set game parameters for faster demo
    game.infection_probability = 0.4
    game.recovery_time = 2
    game.vaccination_cost = 50
    game.infection_penalty = 100
    game.max_vaccinations_per_turn = 3
    
    round_count = 0
    while not game.is_game_over() and round_count < max_rounds:
        round_count += 1
        game.round_number = round_count
        
        # Print current state
        stats = game.get_game_stats()
        print(f"Round {round_count}: S:{stats['S']} I:{stats['I']} R:{stats['R']} V:{stats['V']} Cost:${game.total_cost}")
        
        # Apply automatic vaccination
        nodes_to_vaccinate = game.auto_vaccinate(strategy_name)
        for node in nodes_to_vaccinate:
            game.vaccinate_node(node)
        
        if nodes_to_vaccinate:
            print(f"  Vaccinated nodes: {nodes_to_vaccinate}")
        
        # Spread infection
        new_infections = game.spread_infection()
        if new_infections > 0:
            print(f"  New infections: {new_infections}")
        
        # Update recoveries
        recovered = game.update_recoveries()
        if recovered > 0:
            print(f"  Recovered: {recovered}")
        
        # Small delay for readability
        time.sleep(0.5)
    
    # Final results
    final_stats = game.get_game_stats()
    print(f"\nFinal Results:")
    print(f"Rounds played: {round_count}")
    print(f"Final state: S:{final_stats['S']} I:{final_stats['I']} R:{final_stats['R']} V:{final_stats['V']}")
    print(f"Total cost: ${game.total_cost}")
    print(f"Final rank: {game.get_rank()}")
    print(f"Game ended: {'Disease eradicated' if game.is_game_over() else 'Max rounds reached'}")
    
    return {
        'strategy': strategy_name,
        'network': network_type,
        'rounds': round_count,
        'final_cost': game.total_cost,
        'vaccinations_used': game.vaccinations_used,
        'infections_occurred': game.infections_occurred,
        'final_rank': game.get_rank(),
        'disease_eradicated': game.is_game_over()
    }

def compare_strategies():
    """Compare all vaccination strategies"""
    strategies = ['random', 'ring', 'density', 'greedy']
    networks = ['synthetic', 'erdos_renyi', 'watts_strogatz']
    
    # Use different network sizes for variety
    network_sizes = {'synthetic': 80, 'erdos_renyi': 60, 'watts_strogatz': 70}
    
    results = []
    
    print("🏥 VAXNET STRATEGY COMPARISON 🏥")
    print("=" * 80)
    
    for network in networks:
        num_nodes = network_sizes[network]
        print(f"\nTesting on {network.upper()} network ({num_nodes} nodes):")
        print("-" * 40)
        
        for strategy in strategies:
            result = run_automated_game(strategy, network, num_nodes, max_rounds=15)
            results.append(result)
            print()
    
    # Summary table
    print("\n" + "=" * 80)
    print("SUMMARY COMPARISON")
    print("=" * 80)
    print(f"{'Strategy':<10} {'Network':<15} {'Cost':<8} {'Rounds':<8} {'Rank':<15} {'Eradicated':<10}")
    print("-" * 80)
    
    for result in results:
        print(f"{result['strategy']:<10} {result['network']:<15} ${result['final_cost']:<7} "
              f"{result['rounds']:<8} {result['final_rank']:<15} {str(result['disease_eradicated']):<10}")
    
    # Find best strategy per network
    print("\n" + "=" * 80)
    print("BEST STRATEGIES BY NETWORK")
    print("=" * 80)
    
    for network in networks:
        network_results = [r for r in results if r['network'] == network]
        best_result = min(network_results, key=lambda x: x['final_cost'])
        print(f"{network.upper()}: {best_result['strategy'].upper()} strategy "
              f"(Cost: ${best_result['final_cost']}, Rank: {best_result['final_rank']})")

def demo_visualization():
    """Demo the visualization feature"""
    print("\n🎨 VISUALIZATION DEMO 🎨")
    print("=" * 40)
    
    game = VaxNetGame()
    game.load_network_data("synthetic", 50)  # Smaller network for better visualization
    game.initialize_game(initial_infection_rate=0.15)
    
    print("Initial network state:")
    game.visualize_network()
    
    # Play a few rounds
    for round_num in range(1, 4):
        print(f"\nPlaying round {round_num}...")
        
        # Vaccinate some nodes
        nodes_to_vaccinate = game.auto_vaccinate('greedy')
        for node in nodes_to_vaccinate:
            game.vaccinate_node(node)
        
        # Spread infection
        game.spread_infection()
        game.update_recoveries()
        game.round_number = round_num
        
        print(f"Round {round_num} complete. Visualizing...")
        game.visualize_network()

if __name__ == "__main__":
    print("🎮 VAXNET DEMO MODE 🎮")
    print("This demo will show automated gameplay with different strategies")
    
    choice = input("\nChoose demo type:\n1. Strategy comparison\n2. Visualization demo\n3. Both\nEnter choice (1-3): ").strip()
    
    if choice == "1":
        compare_strategies()
    elif choice == "2":
        demo_visualization()
    elif choice == "3":
        compare_strategies()
        demo_visualization()
    else:
        print("Invalid choice. Running strategy comparison...")
        compare_strategies()
    
    print("\n🎉 Demo complete! Run 'python vaxnet_game.py' for interactive gameplay.") 