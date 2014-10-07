from  matplotlib import pylab

if __name__ == '__main__':
    fh = open('read_lengths.txt')
    L = [int(x.strip()) for x in fh]
    fh.close()
    pylab.hist(L,120, histtype='bar')
    pylab.tight_layout();
    pylab.show()
