#!/bin/bash

for ((N=1000;N<100000;N=N+3000))
do
  ./burbuja $N
done
