import numpy as np
import scipy as sp
import scipy.odr

# data hypotheses
def linear(param, h):
    a, b = param
    return a * h + b

def quadratic(param, h):
    a, b, c = param
    return a * h + b * h**2 + c

def squareroot(param, h):
    a, b = param
    return a * np.sqrt(h) + b

# Test hypothesis using ODR fit to (h, d) data with errors
def test(h, d, hyp, p0, herr, derr, fn):
    md = sp.odr.Model(hyp) # create model using hypothesis
    mdat = sp.odr.RealData(h, d, sx=herr**2, sy=derr**2) # data and uncertainties
    modr = sp.odr.ODR(mdat, md, beta0=p0) # orthogonal distance regression
    output = modr.run()
    
    p = output.beta

    h0 = np.linspace(min(h), max(h), fn)
    return [h0, hyp(p, h0)] # return fit
