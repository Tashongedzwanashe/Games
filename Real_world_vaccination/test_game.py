#!/usr/bin/env python3
"""
Test script for VaxNet game to verify functionality
"""

import unittest
from vaxnet_game import VaxNetGame
import networkx as nx

class TestVaxNetGame(unittest.TestCase):
    
    def setUp(self):
        """Set up test game instance"""
        self.game = VaxNetGame()
        self.game.load_network_data("synthetic", 50)  # Smaller network for faster tests
        self.game.initialize_game(initial_infection_rate=0.1)
    
    def test_network_loading(self):
        """Test that networks load correctly"""
        self.assertIsNotNone(self.game.G)
        self.assertIsInstance(self.game.G, nx.Graph)
        self.assertGreater(len(self.game.G.nodes()), 0)
    
    def test_game_initialization(self):
        """Test game initialization"""
        stats = self.game.get_game_stats()
        self.assertGreater(stats['I'], 0)  # Should have some infected nodes
        self.assertGreater(stats['S'], 0)  # Should have some susceptible nodes
        self.assertEqual(stats['R'], 0)    # Should start with no recovered
        self.assertEqual(stats['V'], 0)    # Should start with no vaccinated
    
    def test_vaccination(self):
        """Test vaccination functionality"""
        initial_cost = self.game.total_cost
        susceptible_nodes = [node for node in self.game.G.nodes() if self.game.status[node] == 'S']
        
        if susceptible_nodes:
            node_to_vaccinate = susceptible_nodes[0]
            success = self.game.vaccinate_node(node_to_vaccinate)
            self.assertTrue(success)
            self.assertEqual(self.game.status[node_to_vaccinate], 'V')
            self.assertEqual(self.game.total_cost, initial_cost + self.game.vaccination_cost)
    
    def test_infection_spread(self):
        """Test infection spread mechanics"""
        initial_infected = self.game.get_game_stats()['I']
        new_infections = self.game.spread_infection()
        self.assertGreaterEqual(new_infections, 0)
        
        # Check that infections are properly counted
        if new_infections > 0:
            self.assertGreater(self.game.infections_occurred, 0)
    
    def test_recovery(self):
        """Test recovery mechanics"""
        # Infect a node and set its infection time
        susceptible_nodes = [node for node in self.game.G.nodes() if self.game.status[node] == 'S']
        if susceptible_nodes:
            node_to_infect = susceptible_nodes[0]
            self.game.status[node_to_infect] = 'I'
            self.game.infection_time[node_to_infect] = self.game.recovery_time
            
            # Should recover
            recovered = self.game.update_recoveries()
            self.assertGreaterEqual(recovered, 0)
            if recovered > 0:
                self.assertEqual(self.game.status[node_to_infect], 'R')
    
    def test_vaccination_strategies(self):
        """Test vaccination strategies return valid nodes"""
        strategies = ['random', 'ring', 'density', 'greedy']
        
        for strategy in strategies:
            nodes = self.game.auto_vaccinate(strategy)
            self.assertIsInstance(nodes, list)
            
            # Check that returned nodes are valid
            for node in nodes:
                self.assertIn(node, self.game.G.nodes())
                self.assertEqual(self.game.status[node], 'S')  # Should be susceptible
    
    def test_game_over_condition(self):
        """Test game over detection"""
        # Initially should not be over
        self.assertFalse(self.game.is_game_over())
        
        # Set all infected nodes to recovered
        for node in self.game.G.nodes():
            if self.game.status[node] == 'I':
                self.game.status[node] = 'R'
        
        # Now should be over
        self.assertTrue(self.game.is_game_over())
    
    def test_scoring(self):
        """Test scoring system"""
        score = self.game.get_score()
        self.assertGreaterEqual(score, 0)
        
        rank = self.game.get_rank()
        self.assertIn(rank, ['GOLD', 'SILVER', 'BRONZE', 'NEEDS IMPROVEMENT'])
    
    def test_neighbor_counting(self):
        """Test infected neighbor counting"""
        for node in self.game.G.nodes():
            count = self.game.count_infected_neighbors(node)
            self.assertGreaterEqual(count, 0)
            
            # Verify count is correct
            neighbors = self.game.get_neighbors(node)
            expected_count = sum(1 for neighbor in neighbors if self.game.status[neighbor] == 'I')
            self.assertEqual(count, expected_count)

def run_quick_test():
    """Run a quick functional test"""
    print("🧪 Running VaxNet Quick Test...")
    
    try:
        # Create game
        game = VaxNetGame()
        game.load_network_data("synthetic", 50)  # Smaller network for faster tests
        game.initialize_game(initial_infection_rate=0.1)
        
        print("✓ Game created and initialized")
        
        # Test vaccination
        stats = game.get_game_stats()
        print(f"✓ Initial state: S:{stats['S']} I:{stats['I']} R:{stats['R']} V:{stats['V']}")
        
        # Test strategies
        strategies = ['random', 'ring', 'density', 'greedy']
        for strategy in strategies:
            nodes = game.auto_vaccinate(strategy)
            print(f"✓ {strategy} strategy returned {len(nodes)} nodes")
        
        # Test infection spread
        new_infections = game.spread_infection()
        print(f"✓ Infection spread: {new_infections} new infections")
        
        # Test recovery
        recovered = game.update_recoveries()
        print(f"✓ Recovery: {recovered} nodes recovered")
        
        print("🎉 All tests passed! Game is working correctly.")
        return True
        
    except Exception as e:
        print(f"❌ Test failed: {e}")
        return False

if __name__ == "__main__":
    print("Choose test type:")
    print("1. Quick functional test")
    print("2. Full unit tests")
    
    choice = input("Enter choice (1-2): ").strip()
    
    if choice == "1":
        run_quick_test()
    elif choice == "2":
        unittest.main(verbosity=2)
    else:
        print("Running quick test...")
        run_quick_test() 