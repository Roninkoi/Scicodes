import numpy as np
from scipy.stats import norm
 
# Separates two classes and calculates
# rejection criteria and probability.
# Input: classes a and b, fraction of class a
# fa, data point x = (x1, x2)
# Output: a rejection criterion a0,
# b selection efficiency be,
# probabilities for classes pa and pb.
def fdisc(a, b, fa, x1, x2):
    acm = np.cov(a[:,0], a[:,1]) # covariances
    bcm = np.cov(b[:,0], b[:,1])
 
    apb = acm + bcm # sum of covariances
    apbi = np.linalg.inv(apb) # invert
 
    # means for classes a and b
    am = np.array((np.mean(a[:,0]), np.mean(a[:,1])))
    bm = np.array((np.mean(b[:,0]), np.mean(b[:,1])))
 
    c = apbi @ (am - bm).T # projection vector
 
    anew = c @ a.T # x3 data
    bnew = c @ b.T
 
    anew = np.sort(anew)
    bnew = np.sort(bnew)
    a0 = anew[int((1. - fa) * len(anew))] # pick value based on fraction
    be = len(bnew[bnew < a0]) / len(bnew) # efficiency
 
    xnew = c @ (x1, x2) # point (x1, x2)
    pa = norm.cdf(xnew, c @ am, np.std(anew)) # calculate probabilities
    pb = 1.-norm.cdf(xnew, c @ bm, np.std(bnew))
 
    return a0, be, pa, pb
 
