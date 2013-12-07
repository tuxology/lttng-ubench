#!/bin/sh

export NR_FUNCS=1000

rm -f dostuff.h dostuff.c dyntp.c ust_tests_benchmark.h

python generate.py dostuff.h.tpl dostuff.h $NR_FUNCS
python generate.py dostuff.c.tpl dostuff.c $NR_FUNCS
python generate.py dyntp.c.tpl dyntp.c $NR_FUNCS
python generate.py ust_tests_benchmark.h.tpl ust_tests_benchmark.h $NR_FUNCS
