#!/bin/bash

for file in $(ls | grep .dat.png)
do
	mv "./$file" "./$(basename ./$file '.dat.png').png"
done

for file in $(ls | grep .png)
do
	mv "./$file" "./$(echo $file | sed 's/\./,/')"
done