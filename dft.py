import numpy as np

# cosine series of signal a (n points) in [-l, l]
def cosseries(a, n, l):
    bw = np.zeros(n)
    bn = np.zeros(n)

    for ni in range(n): # calculate Fourier coefficients
        fi = 0.
        for nxi in range(n):
            x = (nxi / n - 0.5) * l
            fi += a[nxi] * np.cos((ni+1) * np.pi * x / l) * l / n
            
        bw[ni] = ni / n
        bn[ni] = 2. / l * fi

    return np.array([bw, bn]).T

