import numpy as np

def sinpdf(x, f):
    return abs(np.sin(2 * np.pi * f * x))

# Maximum Likelihood estimator for pdf(x) with
# parameter t in range [t0, t1] sampled tn times.
# Returns t, likelihood function max(ln L) and
# ranges of values 1 std around these.
def mle(pdf, t0, t1, tn, x):
    t = t0
    l = 0
    lv = np.zeros(tn)
    tv = np.zeros(tn)

    lmax = -np.inf
    tmax = 0.0
    imax = 0

    for i in range(tn): # go through parameter values
        l = np.sum(np.log(pdf(t, x))) # ln L
        
        lv[i] = l
        tv[i] = t
        
        if (l > lmax):
            lmax = l
            tmax = t
            imax = i
            
        t += (t1 - t0) / (tn - 1)

    # index range for variance estimation
    vi = (np.where(lv<lmax-0.5)[0] - imax)
    vip = np.min(vi[np.where(vi>0)]) + imax
    vin = np.max(vi[np.where(vi<0)]) + imax

    return tmax, lmax, tv[vin:vip], lv[vin:vip]
