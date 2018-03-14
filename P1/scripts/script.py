import subprocess
import struct
import numpy as np
import sys

program = "~/Documents/ALG/P1/quicksort/{} ".format(sys.argv[1])

for x in range(1000,100000,1000):
    mylist = []
    ex = program + str(x)
    for j in range(0,100):
        result = subprocess.check_output(ex, shell=True)
        mylist.append(float(result.decode("utf-8")))
    mean = np.array(mylist).mean()
    print("{} {}".format(x,mean*1000))
