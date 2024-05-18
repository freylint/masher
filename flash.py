
import subprocess
PROGRAMMER = "usbasp"
TARGET = 't84'
TARGET_CLOCK_MHZ = '20'
BIN = "target/avr-attiny84/release/semasher.elf"

#Code By Sam H


command = f"avrdude -c {PROGRAMMER} -p {TARGET} -B{TARGET_CLOCK_MHZ}-U flash:w:{BIN}"
result = subprocess.check_output(command,shell=True,text=True)
print(result)