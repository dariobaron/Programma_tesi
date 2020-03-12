#!/bin/bash

for i in $(seq -0.9 0.1 1)
	do
		./program.x $(echo $i | tr ',' '.')
	done