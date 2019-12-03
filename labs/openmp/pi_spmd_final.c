
#include <omp.h>
#include "logger.h"

#define NUM_THREADS 2

static long steps = 100000;
double step;


int main() {
        int nthreads;
        double pi;
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
		double sum;
		id = omp_get_thread_num();
                nthrds = omp_get_num_threads();
                for(i = id, sum=0.0; i < steps; i = i + nthrds) {
                        x = (i+0.5)*step;
                        sum += 4.0/(1.0+x*x);
                }
		#pragma opm critical
			pi += sum * step;
        }
	run_time = omp_get_wtime() - start_time;
	infof("Pi with %d steps is %f in %f seconds \n",steps,pi,run_time);
        return 0;
}
