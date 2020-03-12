#!/bin/bash

for i in $(seq -0.9 0.1 1)
do
	ii=$(echo $i | tr ',' '.')
	for j in $(seq $ii 0.1 1)
	do
		jj=$(echo $j | tr ',' '.')
		./program.x $ii 0.5 $jj 0.5
	done
done

for i in $(seq -0.9 0.1 1)
do
	ii=$(echo $i | tr ',' '.')
	for j in $(seq -0.9 0.1 1)
	do
		jj=$(echo $j | tr ',' '.')
		./program.x $ii 0.5 $jj 0.25
	done
done