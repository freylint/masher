import os

#This Should work correctly, if not let me know -Sam
os.system("avrdude -c usbasp -p t84 -B 20 -U flash:w:target/avr-attiny84/release/semasher.elf")