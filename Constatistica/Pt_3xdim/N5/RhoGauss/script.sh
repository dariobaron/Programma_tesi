#!/bin/bash

for i in $(seq -0.5 0.1 0.5)
do
	ii=$(echo $i | tr ',' '.')
	for j in $(seq 0 0.2 1)
	do
		jj=$(echo $j | tr ',' '.')
		./program.x $ii $jj
	done
done