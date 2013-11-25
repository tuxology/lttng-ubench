/*
 * bench.c
 *
 * LTTng Userspace Tracer (UST) - benchmark tool
 *
 * Copyright 2010 - Douglas Santos <douglas.santos@polymtl.ca>
 *                  Suchakra Sharma <suchakrapani.sharma@polymtl.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include "dostuff.h"

#ifdef KAJI
#include <signal.h>
#endif

#define tic() do { struct timespec ts_start, ts_end; clock_gettime(CLOCK_MONOTONIC, &ts_start)
#define toc() clock_gettime(CLOCK_MONOTONIC, &ts_end); \
              printf("%lf\n", (ts_end.tv_sec - ts_start.tv_sec) + (double)(ts_end.tv_nsec - ts_start.tv_nsec)/1e9); } \
              while (0)

static int nr_cpus;
static unsigned long nr_events;

void *function(void *arg)
{
	unsigned long i;

	for(i = 0; i < nr_events; i++) {
		do_stuff();
	}
	return NULL;
}

void usage(char **argv) {
	printf("Usage: %s nr_cpus nr_events\n", argv[0]);
}

void signal_handler(int sig) {
    do_stuff();
}

int main(int argc, char **argv)
{

#ifdef KAJI
	signal(SIGUSR1, signal_handler);
	pause();
#endif

	void *retval;
	int i;

	if (argc < 3) {
		usage(argv);
		exit(0);
	}

	nr_cpus = atoi(argv[1]);
	nr_events = atol(argv[2]);

	pthread_t thread[nr_cpus];
	tic();
	for (i = 0; i < nr_cpus; i++) {
		if (pthread_create(&thread[i], NULL, function, NULL)) {
			fprintf(stderr, "thread create %d failed\n", i);
			exit(1);
		}
	}

	for (i = 0; i < nr_cpus; i++) {
		if (pthread_join(thread[i], &retval)) {
			fprintf(stderr, "thread join %d failed\n", i);
			exit(1);
		}
	}
	toc();
	return 0;
}
