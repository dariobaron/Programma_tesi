#!/bin/bash

### Python version
python3 make_plot.py


### Gnuplot version

#for i in $(ls | grep .dat)
#	do
#		gnuplot -e "set terminal png; set output 'Graphs/$i.png'; plot '$i' using 1:2 title 'Measured', '$i' using 1:3 title 'Theory'"
#	done