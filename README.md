# Finding prime numbers using openmpi
Parallel algorithm to find prime numbers in a given interval.

The sequentiel.c file is a sequential algorithm that finds prime numbers in a given interval between 2 and 1 million. A parallel version of this first algorithm written using the MPI library to attempt reducing the run time of the program with large intervals.

The script.sh file allows to automatically run tests to compare the run times of the two versions by varying the number of nodes (N) with different interval sizes.

## Compiling and Running

To compile the main.c file run the following command :
`mpicc main.c -o main`

To run the executable with 4 nodes and find prime numbers between 2 and 1000 : 
`mpiexec main -n 4 2 1000`
