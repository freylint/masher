#! /usr/bin/env python3
"""
SEMasher build script.
"""

import subprocess
import sys


def main():
    # Check if the script was called with 'build' argument
    if len(sys.argv) > 1 and sys.argv[1] == "build":
        # Replace 'script.py' with the name of the script you want to execute
        command = "python3 projects/scripts/build-release.py"

        process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
        out, err = process.communicate()

        # Decode byte string to normal string and print
        print(out.decode("utf-8"))


if __name__ == "__main__":
    main()
