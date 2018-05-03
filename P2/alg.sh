#!/bin/bash
rm *.dat

for ((N=10;N<=8500;N=N+50))
do
  ./eliminarDyV $N >> salidaDyV.dat
  ./eliminarCuadratico $N >> salidaCuad.dat
done