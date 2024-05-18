#! /usr/bin/env python3
"""
SEMasher build script.
"""

import subprocess
import sys


def main():
    # Check if the script was called with 'build' argument
    if len(sys.argv) > 1:

        # Replace 'script.py' with the name of the script you want to execute
        commands = {
            "firmware": "python3 projects/scripts/firmware-rel.py",
            "flash": "python3 projects/scripts/flash.py",
            }

        process = subprocess.Popen(
            commands.get(sys.argv[1]), stdout=subprocess.PIPE, shell=True
        )
        out, err = process.communicate()

        # Decode byte string to normal string and print
        print(out.decode("utf-8"))


if __name__ == "__main__":
    main()
