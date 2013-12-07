#define TRACEPOINT_DEFINE
#define TRACEPOINT_CREATE_PROBES
#include "ust_tests_benchmark.h"

{% for number in range(n) %}
void tpint_{{ number }}(int var)
{
	tracepoint(ust_tests_benchmark, tpint{{ number }}, var);
}
{% endfor %}