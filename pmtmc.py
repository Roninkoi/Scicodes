import numpy as np

# Monte Carlo simulation of a
# photomultiplier tube.
# Input: number of samples n, number of
# dynodes dynum and mean of Poisson
# distribution nu.
# Output: array of numbers of electrons
def pmtmc(n, dynum, nu):
    ens = np.zeros(n) # numbers of electrons
    
    for i in range(n): # get n samples
        en = 1 # initial photoelectron
        for j in range(dynum): # iterate over dynodes
            en0 = en # electrons impacting this dynode
            en = 0
            for k in range(en0): # iterate over electrons
                en += np.random.poisson(nu) # new electrons Poissonian
        ens[i] = en

    return ens
