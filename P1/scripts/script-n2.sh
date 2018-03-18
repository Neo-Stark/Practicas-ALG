#!/bin/bash

for ((N=100;N<10000;N=N+300))
do
  bin/burbujaO2 $N
done