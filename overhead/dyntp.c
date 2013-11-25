#define TRACEPOINT_DEFINE
#define TRACEPOINT_CREATE_PROBES
#include "ust_tests_benchmark.h"

void tpint(int var)
{
	tracepoint(ust_tests_benchmark, tpint, var);
}
