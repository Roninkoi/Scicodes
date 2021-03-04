import numpy as np
from scipy.special import kolmogorov
from scipy.stats import kstwobign

def kolmogorovdiff(dc1, dc2, n1, n2):
    dmax = np.max(np.abs(dc1 - dc2))
    print(np.abs(dc1 - dc2))

    kn = dmax
    if (n2 < 0):
        kn *= np.sqrt(n1)
    else:
        kn *= np.sqrt(n1 * n2 / (n1 + n2))
        
    pks = 1 - kstwobign.cdf(kn)

    return dmax, kn, pks

