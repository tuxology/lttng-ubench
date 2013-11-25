#!/bin/sh

# source ./run

# : ${NR_EVENTS:=1000000}
# : ${NR_CPUS:=1}

LD_PRELOAD=./kaji/src/libkaji.so ./bench_notrace_kaji $NR_CPUS $NR_EVENTS & pid=$!
sleep 1
./kaji/src/client ./bench_notrace_kaji $pid do_stuff+0x4 var
sleep 1
kill -USR1 $pid
wait $pid
