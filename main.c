#include "nbody_header.h"

int main(int argc, char* argv[])
{
	// Input Parameters
	long nBodies = 1000;
	int nthreads = 1;
	double dt = 0.2; 
	int nIters = 1000;
	char * fname = "nbody.dat";

	if(argc > 1)
		nBodies = atol(argv[1]);
	if(argc > 2)
		nIters = atoi(argv[1]);
	if(argc > 3)
		nthreads = atoi(argv[2]);

	// Initialize RNG
	srand(42);

	// Set number of OMP threads if necessary
	#ifdef OPENMP
	omp_set_num_threads(nthreads);
	#endif

	// Initialize MPI
	#ifdef MPI
	MPI_Init(&argc, &argv);
	#endif
	
	// Print Inputs
	print_inputs(nBodies, dt, nIters,nthreads);

	// Run Problem
	#ifdef MPI
	run_parallel_problem(nBodies, dt, nIters, fname);
	#else
	run_serial_problem(nBodies, dt, nIters, fname);
	#endif

	// Finalize MPI
	#ifdef MPI
	MPI_Finalize();
	#endif

	return 0;
}
