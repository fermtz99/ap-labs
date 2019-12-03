#include "omp.h"
#include "logger.h"

int main() {
	#pragma omp parallel
	{
	int ID = omp_get_thread_num();
	infof("hello(%d)", ID);
	infof(" world(%d) \n", ID);
	}
	return 0;
}
