import numpy as np
import matplotlib.pyplot as plt

# (x, y) scatter plot of multiple data sets a
def scatter(a, fpath=""):
    f = plt.figure(figsize=(10, 10))
    plt.rcParams.update({'font.size': 22})
    #colors = plt.cm.plasma(np.linspace(0, 1, len(a)))
    #plt.rcParams['axes.prop_cycle'] = plt.cycler(color=colors)

    i = 1
    for ai in a:
        plt.plot(ai[:, 0], ai[:, 1], marker="o", linestyle="", label="Data " + str(i))
        i += 1
        
    plt.title("Scatter plot")
    plt.xlabel("$x_1$")
    plt.ylabel("$x_2$")
    
    plt.grid(True)
    plt.legend(fontsize='xx-small')
    
    if (len(fpath) > 0):
        f.savefig(fpath, bbox_inches='tight') # save to file

    plt.show()
    plt.close()

