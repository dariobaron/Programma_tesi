#!/bin/bash

make discrepancy.x

./discrepancy.x $(ls | grep .dat)

python3 make_heatmap.py