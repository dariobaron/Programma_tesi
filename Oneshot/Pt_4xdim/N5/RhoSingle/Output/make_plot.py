import os
import numpy
import matplotlib.pyplot as plt

allfilelist = os.listdir(".")

datafile = filter(lambda k: '.dat' in k, allfilelist)

for i in datafile:
	x, ymeasured, ytheory = numpy.loadtxt(i, usecols=(0,1,2), unpack=True)
	plt.ylabel('Fraction of learned dichotomies')
	plt.yticks(numpy.arange(0, 1.2, 0.2))
	plt.xlabel('N° of points')
	x = x.astype(int)
	array_xticks = [k for k in x if k%(x.size/10) == 0]
	plt.xticks(array_xticks)
	title = 'Learning rate for overlap='+i
	title = title.replace('.dat', '')
	plt.suptitle(title)
	plt.plot(x, ymeasured, label='Measured', color='red', marker='x', markersize=10, linestyle='none')
	plt.plot(x, ytheory, label='Model prediction', color='green', marker='o', markersize=10, markerfacecolor='none', linestyle='dashed', linewidth=1)
	plt.legend(loc='upper right')
	plt.savefig('Graphs/'+i+'.png')
	plt.clf()