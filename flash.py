import os
import subprocess

PROGRAMMER = "usbasp"
TARGET = "t84"
TARGET_CLOCK_MHZ = "20"
BIN = "target/avr-attiny84/release/semasher.elf"
# This Should work correctly, if not let me know -Sam
command = f"avrdude -c {PROGRAMMER} -p {TARGET} -B{TARGET_CLOCK_MHZ}-U flash:w:{BIN}"
result = subprocess.check_output(command, shell=True, text=True)
print(result)
