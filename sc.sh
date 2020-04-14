module load compilers/gnu-5.4.0;
./tema2_blas input &> blas.out;
#./tema2_neopt input &> neopt.out;
./tema2_opt_m input &> opt_m.out;
./tema2_opt_f input &> opt_f.out;
./tema2_opt_f_extra input &> opt_f_extra.out;

#qsub -cwd -q ibm-nehalem.q -b n sc.sh