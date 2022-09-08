# !/usr/bash 
# loadspack 
# spack laod libpressio-opt 
# spack unload libpressio-opt
# file=/home/pjyh8/data/hurrican100x500x500/Uf48.bin.f32
# filename=$(basename $file)
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.04  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.05 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.07  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.004  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.005  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.006  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.007  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0004  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0005  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0006  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0007  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00004  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00005  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00006  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00007  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000004  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000005  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000006  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000007  $file | tee -a $filename-zfp.log 



# file=/home/pjyh8/data/hurrican100x500x500/Uf48.bin.f32
# filename=$(basename $file)
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.01 0 1  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.01 0 1  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.05  0 1 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.1 0.1 0.09  0 1 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.001 0 0.1 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.005  0 0.1 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.01 0.01 0.009  0 0.1 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0001 0 0.01 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0005 0 0.01 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.001 0.001 0.0009 0 0.01  $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00001 0  0.001 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00005 0 0.001 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00009 0 0.001 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000001  0 0.0001 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000005  0 0.0001 $file | tee -a $filename-zfp.log 
# mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000009  0 0.0001 $file | tee -a $filename-zfp.log 

file=/home/pjyh8/data/hurrican100x500x500/Pf48.bin.f32
filename=$(basename $file)
mpirun -np 1 ./opt_zfp 0.1 0.1 0.01 0 1  $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.1 0.1 0.01 0 1  $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.1 0.1 0.05  0 1 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.1 0.1 0.09  0 1 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.01 0.01 0.001 0 0.1 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.01 0.01 0.005  0 0.1 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.01 0.01 0.009  0 0.1 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.001 0.001 0.0001 0 0.01 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.001 0.001 0.0005 0 0.01 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.001 0.001 0.0009 0 0.01  $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00001 0  0.001 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00005 0 0.001 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.0001 0.0001 0.00009 0 0.001 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000001  0 0.0001 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000005  0 0.0001 $file | tee -a $filename-zfp.log 
mpirun -np 1 ./opt_zfp 0.00001 0.00001 0.000009  0 0.0001 $file | tee -a $filename-zfp.log 
