import numpy as np
import matplotlib.pyplot as plt

# line + scatter plot of multiple data sets a
# with different labels and styles
def linescatter(a, titles=["", "", ""], labels=[], styles=[], fpath="", show=True, cm=plt.cm.rainbow):
    f = plt.figure(figsize=(10, 10))
    plt.rcParams.update({'font.size': 22})
    colors = cm(np.linspace(0, 1, len(a)))
    plt.rcParams['axes.prop_cycle'] = plt.cycler(color=colors)
    
    i = 0
    for ai in a:
        alabel = "Data " + str(i)
        amarker = ""
        alinestyle = "-"
        
        if len(labels) > 0:
            alabel = labels[i]
            
        if len(styles) > 0:
            if styles[i] == 1:
                amarker = "o"
                alinestyle = ""
                
        plt.plot(ai[:, 0], ai[:, 1], label=alabel, marker=amarker, linestyle=alinestyle)
        i += 1
        
    plt.title(titles[0])
    plt.xlabel(titles[1])
    plt.ylabel(titles[2])
    
    plt.grid(True)
    plt.legend(fontsize='xx-small')

    if len(fpath) > 0:
        f.savefig(fpath, bbox_inches='tight') # save to file

    if show:
        plt.show()
        plt.close()

# line plot with two subplots
def linesub2(a, titles=["", "", ""], labels=[], fpath="", show=True):
    f, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(10, 10))
    plt.rcParams.update({'font.size': 22})
   
    ax1.plot(a[0][:, 0], a[0][:, 1], label=labels[0])
    ax2.plot(a[1][:, 0], a[1][:, 1], color="tab:orange", label=labels[1])
        
    ax1.set_title(titles[0])
    plt.xlabel(titles[1])
    ax1.set_ylabel(titles[2])
    ax2.set_ylabel(titles[2])
    
    ax1.grid(True)
    ax2.grid(True)
    ax1.legend(fontsize='xx-small')
    ax2.legend(fontsize='xx-small')

    if len(fpath) > 0:
        f.savefig(fpath, bbox_inches='tight')

    if show:
        plt.show()
        plt.close()
