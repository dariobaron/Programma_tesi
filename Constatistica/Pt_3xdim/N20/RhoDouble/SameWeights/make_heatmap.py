import numpy
import seaborn
import matplotlib.pyplot as plt
import matplotlib

datafile = numpy.loadtxt("errors.txt", usecols=(0,1,2,3))

xlab = numpy.unique(datafile[:, 0])
ylab = numpy.unique(datafile[:, 1])

#errorvalues = datafile[:, 2:]
#maxval = numpy.amax(errorvalues)

#fig, ax = plt.subplots(2, 1)

discr_mat = numpy.zeros((20,20))
err_stat_mat = numpy.zeros((20,20))

for i in datafile:
	x, y = 9+int(i[0]*10), 9+int(i[1]*10)
	discr_mat[x][y] = i[2]
	err_stat_mat[x][y] = i[3]

matplotlib.rc('xtick', labelsize=6)
matplotlib.rc('ytick', labelsize=6)

seaborn.heatmap(discr_mat, xticklabels=xlab, yticklabels=ylab)#, ax=ax[0])
plt.title("Discrepancy between measures and theoretical predictions")
plt.xlabel('Overlap')
plt.ylabel('Overlap')
plt.savefig("Heatmap_discrepancy.png")

plt.clf()

seaborn.heatmap(err_stat_mat, xticklabels=xlab, yticklabels=ylab)#, ax=ax[1])
plt.title("Statistical dispersion of the measures")
plt.xlabel('Overlap')
plt.ylabel('Overlap')
plt.savefig('Heatmap_statistical.png')