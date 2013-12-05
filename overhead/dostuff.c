#include "dostuff.h"

#ifdef TRACING
#include "ust_tests_benchmark.h"
#endif

volatile int var = 43;

void __attribute__ ((noinline)) do_stuff()
{
    int v = 42;

#ifdef TRACING
	tracepoint(ust_tests_benchmark, tpint, var);
#endif
}
