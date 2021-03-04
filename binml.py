import numpy as np
from scipy.optimize import minimize

# height distribution
def vf(z, k, v0):
    #v0 = 1880. # v0 = n(z = 0)
    drho = 1063. - 997. # density (kg / m^3)
    g = 9.81 # gravity (m / s)
    #r = 0.52e-6 # radius of particle (m)
    r3 = 0.140608 # (e-18 m^3)
    #k = 1.380649e-23 # (m^2 kg / s^2 / K)
    T = 293. # temperature K
    return v0 * np.exp(-4. * np.pi * r3 * drho * g * z / (3. * k * T))

# log-likelihood function
def lnl(x, args):
    k = x[0]
    v0 = x[1]
    z, n = args
    return -np.sum(n * np.log(vf(z, k, v0)) - vf(z, k, v0))

# binned maximum likelihood
def binml(z, n):
    x0 = np.array([1.380649e1, 1880.]) # starting guesses
    mtol = 1e-15
    # minimize -ln L
    res = minimize(lnl, x0, args=np.array([z, n]), method="L-BFGS-B", tol=mtol)
    hinv = res.hess_inv.todense() # inverse of Hessian for covariances
    return res.x, hinv
