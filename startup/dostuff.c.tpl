#include "dostuff.h"

#ifdef TRACING
#include "ust_tests_benchmark.h"
#endif

volatile int var = 43;

{% for number in range(n) %}
void do_stuff_{{ number }} (void) {
    int v = 42;
/*
#ifdef TRACING
	tracepoint(ust_tests_benchmark, tpint, var);
#endif
*/
}
{% endfor %}