#!/bin/bash

set -x

for i in $(find ./ -name Output)
do
	cd $i && ./error.sh
	cd ~/ProgrammaTesi/
done
