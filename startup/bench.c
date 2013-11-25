/*
 * bench.c
 *
 * Copyright 2013 - Suchakra Sharma <suchakrapani.sharma@polymtl.ca>
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
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "dostuff.h"
#include <signal.h>

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
	printf("Usage: %s pid\n", argv[0]);
}

void signal_handler(int sig) {
    do_stuff();
}

int main(int argc, char **argv)
{
    int ret;
#ifdef KAJI
	signal(SIGUSR1, signal_handler);
	pause();
#endif
    ret = kill(atoi(argv[1]), SIGUSR2);
	return 0;
}
