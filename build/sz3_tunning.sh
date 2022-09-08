# !/usr/bash 
loadspack 
spack laod libpressio-opt 
spack unload libpressio-opt
file=/home/pjyh8/data/hurrican100x500x500/Uf48.bin.f32
filename=$(basename $file)

# qoi target                qoi uppwe bound, lower bound
mpirun -np 1 ./opt_demo 0.1 0.1 0.01  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.1 0.1 0.05 $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.1 0.1 0.09  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000009  $file | tee -a $filename.log 


file=/home/pjyh8/data/hurrican100x500x500/Pf48.bin.f32
filename=$(basename $file)
mpirun -np 1 ./opt_demo 0.1 0.1 0.01  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.1 0.1 0.05 $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.1 0.1 0.09  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.01 0.01 0.009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.001 0.001 0.0009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.0001 0.0001 0.00009  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000001  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000005  $file | tee -a $filename.log 
mpirun -np 1 ./opt_demo 0.00001 0.00001 0.000009  $file | tee -a $filename.log 


// x^2 error 0.1 
// 

serach space 0.01 - 0.1 

lua restrction 0.09 - 0.1  
