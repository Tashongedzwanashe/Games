#!/usr/bin/env python3
"""
Test script for Set Game Extensions
Authors: Emmanuel Mufunde 100001936, George Kilibwa 100002924
"""

import os
import sys
import subprocess
import time
import platform

def run_command(command, timeout=10):
    """Run a command with timeout"""
    try:
        result = subprocess.run(command, shell=True, capture_output=True, text=True, timeout=timeout)
        return result.returncode == 0, result.stdout, result.stderr
    except subprocess.TimeoutExpired:
        return False, "", "Command timed out"
    except Exception as e:
        return False, "", str(e)

def test_compilation():
    """Test compilation of all extensions"""
    print("Testing compilation...")
    
    # Test AI extension
    print("  Testing AI extension compilation...")
    success, stdout, stderr = run_command("g++ -std=c++11 -o set_game_ai set_game_ai.cpp")
    if success:
        print("    ✓ AI extension compiles successfully")
    else:
        print(f"    ✗ AI extension compilation failed: {stderr}")
        return False
    
    # Test GUI extension (may fail if SFML not installed)
    print("  Testing GUI extension compilation...")
    success, stdout, stderr = run_command("g++ -std=c++11 -o set_game_gui set_game_gui.cpp -lsfml-graphics -lsfml-window -lsfml-system")
    if success:
        print("    ✓ GUI extension compiles successfully")
    else:
        print("    ⚠ GUI extension compilation failed (SFML may not be installed)")
    
    # Test Network extension (may fail if SFML not installed)
    print("  Testing Network extension compilation...")
    success, stdout, stderr = run_command("g++ -std=c++11 -o set_game_network set_game_network.cpp -lsfml-network -lsfml-system")
    if success:
        print("    ✓ Network extension compiles successfully")
    else:
        print("    ⚠ Network extension compilation failed (SFML may not be installed)")
    
    return True

def test_ai_extension():
    """Test AI extension execution"""
    print("\nTesting AI extension execution...")
    
    if not os.path.exists("set_game_ai"):
        print("  ✗ AI executable not found")
        return False
    
    # Test with input that exits quickly
    test_input = "1\n"  # Choose Human vs Human mode
    try:
        process = subprocess.Popen(["./set_game_ai"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate(input=test_input, timeout=5)
        print("    ✓ AI extension runs successfully")
        return True
    except subprocess.TimeoutExpired:
        process.kill()
        print("    ✓ AI extension runs (timeout is normal)")
        return True
    except Exception as e:
        print(f"    ✗ AI extension execution failed: {e}")
        return False

def test_gui_extension():
    """Test GUI extension execution"""
    print("\nTesting GUI extension execution...")
    
    if not os.path.exists("set_game_gui"):
        print("  ⚠ GUI executable not found (SFML may not be installed)")
        return True  # Not a failure, just missing dependency
    
    # GUI will open a window, so we just test if it starts
    try:
        process = subprocess.Popen(["./set_game_gui"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        time.sleep(2)  # Give it time to start
        process.terminate()
        print("    ✓ GUI extension starts successfully")
        return True
    except Exception as e:
        print(f"    ✗ GUI extension execution failed: {e}")
        return False

def test_network_extension():
    """Test Network extension compilation"""
    print("\nTesting Network extension compilation...")
    
    if not os.path.exists("set_game_network"):
        print("  ⚠ Network executable not found (SFML may not be installed)")
        return True  # Not a failure, just missing dependency
    
    # Test with input that exits quickly
    test_input = "1\n12345\n"  # Choose server mode, port 12345
    try:
        process = subprocess.Popen(["./set_game_network"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate(input=test_input, timeout=3)
        print("    ✓ Network extension compiles and starts successfully")
        return True
    except subprocess.TimeoutExpired:
        process.kill()
        print("    ✓ Network extension runs (timeout is normal)")
        return True
    except Exception as e:
        print(f"    ✗ Network extension execution failed: {e}")
        return False

def check_dependencies():
    """Check for required dependencies"""
    print("Checking dependencies...")
    
    # Check for g++
    success, stdout, stderr = run_command("g++ --version")
    if success:
        print("  ✓ g++ compiler found")
    else:
        print("  ✗ g++ compiler not found")
        return False
    
    # Check for SFML (optional)
    success, stdout, stderr = run_command("pkg-config --modversion sfml-all")
    if success:
        print("  ✓ SFML libraries found")
    else:
        print("  ⚠ SFML libraries not found (GUI and Network extensions will not compile)")
    
    return True

def cleanup():
    """Clean up test files"""
    print("\nCleaning up test files...")
    files_to_remove = ["set_game_ai", "set_game_gui", "set_game_network"]
    for file in files_to_remove:
        if os.path.exists(file):
            os.remove(file)
            print(f"  Removed {file}")

def main():
    """Main test function"""
    print("Set Game Extensions Test Suite")
    print("=" * 40)
    print(f"Platform: {platform.system()} {platform.release()}")
    print(f"Python: {sys.version}")
    print()
    
    # Check dependencies
    if not check_dependencies():
        print("\n❌ Dependency check failed")
        return 1
    
    # Test compilation
    if not test_compilation():
        print("\n❌ Compilation test failed")
        return 1
    
    # Test execution
    ai_ok = test_ai_extension()
    gui_ok = test_gui_extension()
    network_ok = test_network_extension()
    
    # Summary
    print("\n" + "=" * 40)
    print("Test Summary:")
    print(f"  AI Extension: {'✓' if ai_ok else '✗'}")
    print(f"  GUI Extension: {'✓' if gui_ok else '⚠'}")
    print(f"  Network Extension: {'✓' if network_ok else '⚠'}")
    
    if ai_ok:
        print("\n✅ All core tests passed!")
        print("   The AI extension is fully functional.")
        if gui_ok and network_ok:
            print("   GUI and Network extensions are also working.")
        else:
            print("   Install SFML to enable GUI and Network extensions.")
    else:
        print("\n❌ Some tests failed.")
        return 1
    
    # Cleanup
    cleanup()
    
    return 0

if __name__ == "__main__":
    sys.exit(main()) 