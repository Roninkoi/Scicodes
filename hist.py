import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as sps

# histogram plot
def hist(x, nbins, fpath=""):
    f = plt.figure(figsize=(10, 10))
    plt.rcParams.update({'font.size': 22})
    #colors = plt.cm.plasma(np.linspace(0, 1, len(a)))
    #plt.rcParams['axes.prop_cycle'] = plt.cycler(color=colors)

    # generate (normalized) histogram of data x
    plt.hist(x, nbins, ec="tab:blue", label="Random data", density=True)

    x0 = np.linspace(min(x), max(x), nbins * 10)
    mu = np.mean(x) # mean of Gaussian
    std = np.std(x) # standard deviation of Gaussian

    # plot normal distribution to compare to data
    plt.plot(x0, sps.norm.pdf(x0, loc=mu, scale=std), label="N("+"%.2e"%mu+", "+"%.2e"%(std**2)+")")
    
    plt.title("Histogram")
    plt.xlabel("$x$")
    plt.ylabel("$N$")
    
    plt.grid(True)
    plt.legend(fontsize='xx-small')

    if (len(fpath) > 0):
        f.savefig(fpath, bbox_inches='tight') # save to file

    plt.show()
    plt.close()

