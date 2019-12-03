#include <omp.h>
#include "logger.h"

#define NUM_THREADS 3

static long steps = 100000;
double step;


int main() {
	int i;
	int nthreads;
	double pi = 0.0;
	double sum [NUM_THREADS];
	double start_time, run_time;
	step = 1.0/(double) steps;
	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
	#pragma omp parallel
	{
		int i;
		int id;
		int nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if(id == 0)
			nthreads = nthrds;
		for(i = id, sum[id]=0.0; i < steps; i = i + nthrds) {
			x = (i+0.5)*step;
			sum[id] += 4.0/(1.0+x*x);
		}
	}
	for(i = 0, pi = 0.0; i < nthreads; i++)
		pi += sum[i] * step;
	run_time = omp_get_wtime() - start_time;
	infof("pi with %d steps is %f in %f seconds \n",steps,pi,run_time);
	infof("Number of threads: %d\n", nthreads);
	return 0;
}
