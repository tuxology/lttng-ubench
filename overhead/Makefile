all: dyntp.so mutator bench_notrace bench_trace bench_notrace_kaji 
	$(MAKE) -C kaji

dyntp.so: dyntp.o
	gcc -shared  -fPIC -DPIC $^ -ldl -llttng-ust -o $@

dyntp.o: dyntp.c ust_tests_benchmark.h
	gcc -I. -fno-strict-aliasing -Wall -g -c $< -fPIC -DPIC -o $@

tp.o: tp.c ust_tests_benchmark.h
	gcc -I. -fno-strict-aliasing -Wall -g -c $< -o $@

mutator: mutator.o
	g++ -g $^ -L/usr/lib64/dyninst -Wl,-rpath=/usr/lib64/dyninst -ldyninstAPI -o $@

mutator.o: mutator.cpp
	g++ -g $< -c -o $@

dostuff.o: dostuff.c dostuff.h tp.o
	gcc -I. -std=gnu99 -g -DTRACING -c $< -o $@

dostuff_notrace.o: dostuff.c dostuff.h tp.o
	gcc -I. -std=gnu99 -g -c $< -o $@

bench_trace: bench_trace.o tp.o dostuff.o
	gcc $^ -std=gnu99 -g -O2 -lrt -ldl -llttng-ust -lpthread -o $@

bench_trace.o: bench.c
	gcc $< -std=gnu99 -g -O2 -DTRACING -c -o $@

bench_notrace: bench_notrace.o dostuff_notrace.o
	gcc $^ -std=gnu99 -g -O2 -lrt -lpthread -o $@

bench_notrace.o: bench.c
	gcc $< -std=gnu99 -g -O2 -c -o $@

bench_notrace_kaji: bench_notrace_kaji.o dostuff_notrace.o
	gcc $^ -std=gnu99 -g -O2 -lrt -lpthread -o $@

bench_notrace_kaji.o: bench.c
	gcc $< -std=gnu99 -g -O2 -DKAJI -c -o $@

.PHONY: clean
clean:
	rm -f *.o *.so mutator bench_notrace bench_trace bench_notrace_kaji
	$(MAKE) -C kaji clean
