import numpy
import seaborn
import matplotlib.pyplot as plt
import matplotlib

datafile = numpy.loadtxt("errors.txt", usecols=(0,1,2,3))

xlab = numpy.unique(datafile[:, 0])
ylab = numpy.unique(datafile[:, 1])

discr_mat = numpy.zeros((ylab.size,xlab.size))
err_stat_mat = numpy.zeros((ylab.size,xlab.size))

for i in range(ylab.size):
	row_with_y = numpy.where(datafile[:,1]==ylab[i])[0]
	for j in range(xlab.size):
		row_with_x = numpy.where(datafile[:,0]==xlab[j])[0]
		row = numpy.intersect1d(row_with_x, row_with_y)
		discr_mat[i][j] = datafile[row, 2]
		err_stat_mat[i][j] = datafile[row, 3]

matplotlib.rc('xtick', labelsize=6)
matplotlib.rc('ytick', labelsize=6)

seaborn.heatmap(discr_mat, xticklabels=xlab, yticklabels=ylab)#, ax=ax[0])
plt.title("Discrepanza tra misura e predizione teorica")
plt.xlabel('Overlap medio')
plt.ylabel('Dispersione')
plt.savefig("Heatmap_discrepancy.png")

plt.clf()

seaborn.heatmap(err_stat_mat, xticklabels=xlab, yticklabels=ylab)#, ax=ax[1])
plt.title("Incertezza statistica delle misure")
plt.xlabel('Overlap medio')
plt.ylabel('Dispersione')
plt.savefig('Heatmap_statistical.png')