#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>

void eat(int n);
void think(int n);
void signal_handler(int signum);

int main(int argc, char* argv[]) {
    sem_t chopstick[5];
    unsigned int usecs;
    int n, m;
    n = 0;
    m = 0;

    int i;
    i = 0;

    usecs = rand();

    signal(SIGTERM, signal_handler);   

    while(1) {
        printf("Processing things #%d.\n", i);
        i++;
        sleep(1);
    }

/*
    do { 
        // wait(chopstick[i]);
        // wait(chopstick[(i+1)]);
        /* ...
        eat for awhile
        // signal(SIGTERM, eat)
        
        printf("Sleeping now..\n");
        usleep(random);
        signal(SIGTERM, signal_handler);
        //signal(chopstick[i], think);
        //signal(chopstick[(i+1)], think);
        /* ...
        think for awhile
    } while(true);
    */

    return EXIT_SUCCESS;

}

// signal handler for SIGTERM when cmd 'kill -TERM pid' is called
void signal_handler(int signum) {
    fprintf(stderr, "Philosopher #n completed m cycles\n");
    printf("Caught signal %d\n", signum);
    exit(signum);
}

void eat(int n){
    printf("Philosopher #%d is eating", n);
    exit(1);
}

void think(int n){
    printf("Philosopher #%d is thinking", n);
    exit(1);
}


// ps -aux | grep dining-p
// kill -TERM 'pid'