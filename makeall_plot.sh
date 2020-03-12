#!/bin/bash

set -x

for i in $(find ./ -name Output)
do
	cd $i && ./plot.sh
	cd ~/ProgrammaTesi/
done

for i in $(find ./ -name SameWeights)
do
	cd $i && ./plot.sh
	cd ~/ProgrammaTesi/
done

for i in $(find ./ -name DiffWeights)
do
	cd $i && ./plot.sh
	cd ~/ProgrammaTesi/
done