#!/bin/bash

set -x

for i in $(find ./ -name SameWeights)
do
	cd $i && ./heatmap.sh
	cd ~/ProgrammaTesi/
done

for i in $(find ./ -name DiffWeights)
do
	cd $i && ./heatmap.sh
	cd ~/ProgrammaTesi/
done