!/bin/bash
PDIR=profdir.$PMI_RANK
export GMON_OUT_PREFIX=${GMON_OUT_PREFIX:-gmon.out.mpi}.$PMI_RANK
exec $@
file=/home/pjyh8/data/hurrican100x500x500/Pf48.bin.f32
chmod o+x gprof-wrapper
mpiexec -n 1 ./opt_zfp 0.1 0.1 0.01 0 1  $file 
gprof ./opt_zfp.exe ./gmon.out.mpi.*