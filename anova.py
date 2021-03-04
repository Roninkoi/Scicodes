import numpy as np
from scipy.stats import f

# Does analysis of variance for a number of sets x.
# Each set in x is an array containing mean, variance
# and number [mean, var, n].
def anova(x):
    mean = np.mean(x[:, 0]) # overall mean
    n = np.sum(x[:, 2]) # total N
    r = len(x) # number of sets

    ssb = 0.
    for i in range(r): # sum of squares between sets
        ssb += x[i, 2] * (x[i, 0] - mean)**2

    ssw = 0.
    for i in range(r): # sum of squares within sets
        ssw += (x[i, 2] - 1) * x[i, 1]

    fs = (ssb / (r - 1)) / (ssw / (n - r))
    dfn, dfd = r - 1, n - r # degrees of freedom
    p = f.cdf(fs, dfn, dfd) # P-value from F-distribution

    return fs, p
