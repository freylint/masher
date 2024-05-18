import subprocess

CMD = """
make -C projects/firmware
"""

process = subprocess.Popen(CMD, stdout=subprocess.PIPE, shell=True)
out, err = process.communicate()

# Decode byte string to normal string and print
print(out.decode("utf-8"))
