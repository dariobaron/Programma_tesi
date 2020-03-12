#!/bin/bash

### Python version
python3 make_plot.py


### Gnuplot version

#for i in $(ls | grep .dat)
#	do
#		cp ./$i ./$i.temp
#		sed -n s/'+-'/''/g ./$i.temp
#		gnuplot -e "set terminal png; set output 'ErrGraphs/$i.png'; set yrange [0:1]; plot '$i.temp' using 1:2:4 with yerrorbars title 'Measured', '$i.temp' using 1:5 title 'Theory'"
#		rm ./$i.temp
#	done