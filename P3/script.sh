#!/bin/bash

rm tiempos.dat
rm distancias.dat
echo "a280\n" >> distancias.dat
echo "a280\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f %e -a -o tiempos.dat ./viajante$i datosTSP/a280.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-a280.tsp
done

echo "att48\n" >> distancias.dat
echo "att48\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/att48.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-att48.tsp
done
echo "berlin52\n" >> distancias.dat
echo "berlin52\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/berlin52.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-berlin52.tsp
done
echo "ch130\n" >> distancias.dat
echo "ch130\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/ch130.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-ch130.tsp
done
echo "eil101\n" >> distancias.dat
echo "eil101\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/eil101.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-eil101.tsp
done
echo "gr202\n" >> distancias.dat
echo "gr202\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/gr202.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-gr202.tsp
done
echo "tsp225\n" >> distancias.dat
echo "tsp225\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/tsp225.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-tsp225.tsp
done
echo "pa561\n" >> distancias.dat
echo "pa561\n" >> tiempos.dat
for((i=1;i<4;i=i+1))
do
   /usr/bin/time -f " viajante$i \t%e" -a -o tiempos.dat ./viajante$i datosTSP/pa561.tsp >> distancias.dat
   mv salida.tsp salidas/viajante$i-pa561.tsp
done