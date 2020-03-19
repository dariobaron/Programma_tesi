#!/bin/bash

./discrepancy.x $(ls | grep .dat)

python3 make_heatmap.py