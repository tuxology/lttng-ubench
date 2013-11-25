#include "dostuff.h"

#ifdef TRACING
#include "ust_tests_benchmark.h"
#endif

volatile int var = 43;

void __attribute__ ((noinline)) do_stuff()
{
	//FILE *file;
    int v = 42;
#if 0
	file = fopen("/dev/null", "a");
	fprintf(file, "%d", v);
	fclose(file);
	time(NULL);
#endif

#ifdef TRACING
	tracepoint(ust_tests_benchmark, tpint, var);
#endif
}
