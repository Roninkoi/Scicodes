import numpy as np

# Generates a random number following the
# Breit-Wigner distribution.
# Input: array of random numbers r in range [0, 1],
#        Breit-Wigner parameters es (mean) and gs (uncertainty)
def breitwigner(r, es, gs):
    return es + gs / 2 * np.tan((2 * r - 1) * np.pi / 2)
