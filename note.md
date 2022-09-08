[main topic]

how to properly configure the search space?

the upper bound, lower bound, searching setps

appropriate algorithm for our single thread application


[implmentation]
where should I locate the implmentatio of the 

C and CXX compatbility 



[misc] 

spack will fail to load some packages in the incldue path, so I have to add them manually bt "export CPLUS_INCLUDE_PATH=" 

latest spack version fails to load packages into the, open issue on github. 

libpressio-opt won't work with gcc 7.5, indicated by on the repository supporting gcc 8.2+




cmake -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg -DCMAKE_SHARED_LINKER_FLAGS=-pg


 valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes mpirun -np 1 ./opt_zfp 0.1 0.1 0.01 0 1 /home/pjyh8/data/hurrican100x500x500/Pf48.bin.f32