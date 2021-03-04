import numpy as np

# Generate Poissonian pseudodata from x with n samples
# and perform chi2 test. Calculate P-value for chi2 > ochi2.
def pseudochi(x, n, ochi2):
    chi = np.empty(n)
    
    for i in range(n):
        poi = np.random.poisson(x) # generate Poisson distribution
        chix, _ = chisquare(poi, x) # get chi2 value
        chi[i] = chix
        
    hist, histbins = np.histogram(chi, n)
    cdf = np.cumsum(hist) # generate cdf
    cdf = cdf / np.max(cdf)

    p = 1.0
    for i in range(len(cdf)):
        if (histbins[i] >= ochi2): # get P-value from cdf
            p = cdf[i]
            break

    return chi, hist, histbins, p
