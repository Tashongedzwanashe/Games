#!/usr/bin/env python3
"""
VaxNet Game Launcher
Provides easy access to all game features
"""

import sys
import os

def main():
    print("🎮 VAXNET GAME LAUNCHER 🎮")
    print("=" * 40)
    print("Choose an option:")
    print("1. Play Interactive Game")
    print("2. Run Demo (Automated Strategies)")
    print("3. Run Tests")
    print("4. Install Dependencies")
    print("5. Exit")
    
    while True:
        try:
            choice = input("\nEnter your choice (1-5): ").strip()
            
            if choice == "1":
                print("\nStarting interactive game...")
                os.system("python vaxnet_game.py")
                break
                
            elif choice == "2":
                print("\nStarting demo...")
                os.system("python demo.py")
                break
                
            elif choice == "3":
                print("\nRunning tests...")
                os.system("python test_game.py")
                break
                
            elif choice == "4":
                print("\nInstalling dependencies...")
                os.system("pip install -r requirements.txt")
                print("Dependencies installed successfully!")
                break
                
            elif choice == "5":
                print("Goodbye! 👋")
                break
                
            else:
                print("Invalid choice. Please enter 1-5.")
                
        except KeyboardInterrupt:
            print("\n\nGoodbye! 👋")
            break
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main() 