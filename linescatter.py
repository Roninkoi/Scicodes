import numpy as np
import matplotlib.pyplot as plt

# line + scatter plot of multiple data sets a
# with different labels and styles
def linescatter(a, titles=["", "", ""], labels=[], styles=[], fpath=""):
    f = plt.figure(figsize=(10, 10))
    plt.rcParams.update({'font.size': 22})
    #colors = plt.cm.plasma(np.linspace(0, 1, len(a)))
    #plt.rcParams['axes.prop_cycle'] = plt.cycler(color=colors)

    i = 0
    for ai in a:
        alabel = "Data " + str(i)
        amarker = ""
        alinestyle = "-"
        
        if (len(labels) > 0):
            alabel = labels[i]
            
        if (len(styles) > 0):
            if (styles[i] == 1):
                amarker = "o"
                alinestyle = ""
                
        plt.plot(ai[:, 0], ai[:, 1], label=alabel, marker=amarker, linestyle=alinestyle)
        i += 1
        
    plt.title(titles[0])
    plt.xlabel(titles[1])
    plt.ylabel(titles[2])
    
    plt.grid(True)
    plt.legend(fontsize='xx-small')

    if (len(fpath) > 0):
        f.savefig(fpath, bbox_inches='tight') # save to file

    plt.show()
    plt.close()

