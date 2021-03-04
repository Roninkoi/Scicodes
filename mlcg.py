import numpy as np
import time

# Generates n random numbers in range [0, 1]
# using a multiplicative linear congruential generator.
def rand(n):
    xs = time.time() # seed

    # LCG parameters
    a = 40692
    c = 0 # MLCG
    m = 2147483399

    x = np.empty(n)
    
    for i in range(n):
        xn = (a * xs + c) % m # recurrence
        xs = xn
        x[i] = xn / (m - 1) # normalize

    return x
