import numpy as np

# Scheffe maximal statistical difference
def msdij(x, p, i, j):
    var = np.mean(x[:, 1]) # mean variance
    n = np.sum(x[:, 2]) # total N
    ni = 1.0 / x[i, 2] + 1.0 / x[j, 2] # sum of inverse N
    r = len(x) # number of sets

    dfn, dfd = r - 1, n - r # degrees of freedom
    fs = f.ppf(p, dfn, dfd) # F-value corresponding to P

    return np.sqrt((r - 1) * fs * var * ni)
