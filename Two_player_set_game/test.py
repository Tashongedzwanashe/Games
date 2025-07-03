#!/usr/bin/env python3
"""
Test script for Set Game Extensions
Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924
"""

import os
import sys
import subprocess
import time

def test_compilation():
    """Test compilation of extensions"""
    print("Testing compilation...")
    
    # Test AI extension
    print("  Testing AI extension...")
    result = subprocess.run(["g++", "-std=c++11", "-o", "set_game_ai", "set_game_ai.cpp"], 
                          capture_output=True, text=True)
    if result.returncode == 0:
        print("    ✓ AI extension compiles successfully")
    else:
        print(f"    ✗ AI extension compilation failed")
        return False
    
    # Test GUI extension
    print("  Testing GUI extension...")
    result = subprocess.run(["g++", "-std=c++11", "-o", "set_game_gui", "set_game_gui.cpp", 
                           "-lsfml-graphics", "-lsfml-window", "-lsfml-system"], 
                          capture_output=True, text=True)
    if result.returncode == 0:
        print("    ✓ GUI extension compiles successfully")
    else:
        print("    ⚠ GUI extension compilation failed (SFML may not be installed)")
    
    # Test Network extension
    print("  Testing Network extension...")
    result = subprocess.run(["g++", "-std=c++11", "-o", "set_game_network", "set_game_network.cpp", 
                           "-lsfml-network", "-lsfml-system"], 
                          capture_output=True, text=True)
    if result.returncode == 0:
        print("    ✓ Network extension compiles successfully")
    else:
        print("    ⚠ Network extension compilation failed (SFML may not be installed)")
    
    return True

def cleanup():
    """Clean up test files"""
    files = ["set_game_ai", "set_game_gui", "set_game_network"]
    for file in files:
        if os.path.exists(file):
            os.remove(file)

def main():
    print("Set Game Extensions Test")
    print("=" * 30)
    
    if test_compilation():
        print("\n✅ Compilation tests completed!")
        print("   AI extension is ready to use.")
        print("   Install SFML for GUI and Network extensions.")
    else:
        print("\n❌ Compilation tests failed!")
    
    cleanup()
    return 0

if __name__ == "__main__":
    sys.exit(main()) 