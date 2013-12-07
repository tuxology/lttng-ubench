lttng-ubench
============

Micro benchmarks for LTTng/UST - mainly for dynamic userspace tracing

The total time for 1st execution is calculated as
### __T<sub>_total_</sub> = T<sub>_exec_</sub> + T<sub>_instr_</sub> + T<sub>_reg_</sub>__ ###

There are different benchmarks for each new type of test so that we get T<sub>_exec_</sub>, T<sub>_reg_</sub> and T<sub>_instr_</sub>

Installing
----------
Requires all dependencies for Kaji as well as Dyninst

`git submodule init` and then `make` 

Usage
------
* Go through the script `run.sh`. Some manual tweaking is required for now (for example, 
changing the `NR_CPUS` and `NR_EVENTS`).
Make sure `EV_OR_CPUS` is set properly in the script. 
* Use `plot.sh [overhead | scalability]` to consolidate results and plot graphs (requires `gnuplot`)


TODO
----
* Make this more modular
* Add more and better tests
