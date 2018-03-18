#!/bin/bash

for ((N=1000;N<100000;N=N+3000))
do
  bin/mergeSort $N
done
