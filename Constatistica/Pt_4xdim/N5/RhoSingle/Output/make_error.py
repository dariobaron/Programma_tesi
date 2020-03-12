import numpy
import matplotlib.pyplot as plt

datafile = numpy.loadtxt("errors.txt", usecols=(0,1,2,3))

datafile = datafile[datafile[:,0].argsort()]

x = datafile[:, 0]
ydisc = datafile[:, 1]
ystat = datafile[:, 2]

#plt.plot(x, ydisc, color='blue', marker='o', linestyle='dashed', linewidth=2, markersize=12)
#plt.title("Discrepancy between measures and theoretical predictions")
#plt.xlabel('Overlap')
#plt.ylabel('Discrepancy')
#plt.tight_layout()
#plt.savefig("error_discrepancy.png")

#plt.clf()

#plt.plot(x, ystat, color='green', marker='o', linestyle='dashed', linewidth=2, markersize=12)
#plt.title("Statistical dispersion of the measures")
#plt.xlabel('Overlap')
#plt.ylabel('Dispersion')
#plt.savefig('error_statistical.png

plt.plot(x, ydisc, color='red', marker='o', linestyle='dashed', linewidth=2, markersize=8, label='Discrepanza')
plt.plot(x, ystat, color='blue', marker='o', linestyle='dotted', linewidth=2, markersize=8, label='Incertezza statistica')
plt.legend()
plt.title("Confronto tra discrepanza e incertezza statistica al variare dell'overlap")
plt.xlabel('Overlap')
plt.ylabel('Somma scarti quadratici')
plt.tight_layout()
plt.savefig("error.png")