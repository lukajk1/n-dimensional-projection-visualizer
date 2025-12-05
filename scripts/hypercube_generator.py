#!/usr/bin/env python3
import sys

END_DIMENSION = 10

def main():
    # --- Your program's main logic goes here ---
    print("The script is running!")
    # For a simple script, you might call other functions or perform tasks.
    # -------------------------------------------
    
    # Wait for the user to press Enter before closing (especially useful on Windows)
    if sys.platform.startswith('win'):
        input("\nPress Enter to exit...")

if __name__ == "__main__":
    main()
