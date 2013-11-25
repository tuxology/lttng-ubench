#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <wait.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

/*#define tic() do { struct timespec ts_start, ts_end; clock_gettime(CLOCK_MONOTONIC, &ts_start)*/
/*#define toc() clock_gettime(CLOCK_MONOTONIC, &ts_end); \*/
              /*printf("%lf\n", (ts_end.tv_sec - ts_start.tv_sec) + (double)(ts_end.tv_nsec - ts_start.tv_nsec)/1e9); } \*/
              /*while (0)*/

struct timespec ts_start, ts_end;

void tic(){
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
}

void toc(){
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    printf("%lf\n", (ts_end.tv_sec - ts_start.tv_sec) + (double)(ts_end.tv_nsec - ts_start.tv_nsec)/1e9);

}
void signal_handler(int sig) {
    toc();
}

int main(int argc, char **argv)
{
    if (argc < 2){
        printf("Too few args..\n");
    }
    int pid = fork();
    tic();
    if (pid == 0){
        char pid_str[15];
        sprintf(pid_str, "%d", (int) getppid());
        int ret= execl(argv[1], argv[1], pid_str, (char*) NULL); //argv[1] is bench_nomain
        if (ret < 1)
            printf("execl : %s\n", strerror(errno));
    }
    else{
        signal(SIGUSR2, signal_handler);
        pause();
    }
	return 0;
}

