import subprocess
import os 

cmd1 = "clang-format -i *.h"
cmd2 = "clang-format -i *.c"
cmd3 = "python3 -m black *.py"

#First Format Command
os.system(cmd1)
print("Format .h Done")

#Second Format Command
os.system(cmd2)
print("Format .c Done")

#Running The Reqested File
result = subprocess.check_output(cmd3,shell=True,text=True)
print(result)
