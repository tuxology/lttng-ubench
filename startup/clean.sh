#!/bin/sh

echo "Cleaning results & plots..."
rm -rf results/* plots/*

echo "Cleaning old generated files..."
rm -f dostuff.c dostuff.h ust_tests_benchmark.h dyntp.c
