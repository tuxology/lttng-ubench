#include "ust_tests_benchmark.h"
{% for number in range(n) %}
void do_stuff_{{ number }}(void);
{% endfor %}
