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
#include <pthread.h>

#define SEM_FILE0 "/sally_chopstick_0"
#define SEM_FILE1 "/sally_chopstick_1"
#define SEM_FILE2 "/sally_chopstick_2"
#define SEM_FILE3 "/sally_chopstick_3"
#define SEM_FILE4 "/sally_chopstick_4"

void signal_handler(sem_t* chopstick[], int n, int m, int signum);
void eat(int n);
void think(int n);
void wait2(sem_t* chopstick);
void signal2(sem_t* chopstick);

int main(int argc, char* argv[]) {
    sem_t* chopstick[5];
    unsigned int usecs;
    int n, m;
    n = 0;
    m = 0;

    int i;
    i = 0;

    chopstick[0] = sem_open(SEM_FILE0, O_CREAT|O_EXCL, 0666, 1);
    chopstick[1] = sem_open(SEM_FILE1, O_CREAT|O_EXCL, 0666, 1);
    chopstick[2] = sem_open(SEM_FILE2, O_CREAT|O_EXCL, 0666, 1);
    chopstick[3] = sem_open(SEM_FILE3, O_CREAT|O_EXCL, 0666, 1);
    chopstick[4] = sem_open(SEM_FILE4, O_CREAT|O_EXCL, 0666, 1);


    // signal(SIGTERM, signal_handler);   

    while(1) {
        printf("Processing things #%d.\n", i);
        i++;
        sleep(1);
    }

    do { 
        wait2(chopstick[i]);
        wait2(chopstick[(i+1) % 5]);
        //eat for awhile
        eat(n);
        // signal(SIGTERM, eat)
        
        printf("Sleeping now..\n");
        sleep(1);
        // signal(SIGTERM, signal_handler);
        signal2(chopstick[i]);
        signal2(chopstick[(i+1) % 5]);
        // think for awhile
        think(n);
    } while(true);

    return EXIT_SUCCESS;

}

// signal handler for SIGTERM when cmd 'kill -TERM pid' is called
void signal_handler(sem_t* chopstick[], int n, int m, int signum) {
    sem_close(chopstick[0]);
    sem_close(chopstick[1]);
    sem_close(chopstick[2]);
    sem_close(chopstick[3]);
    sem_close(chopstick[4]);

    sem_unlink(SEM_FILE0);
    sem_unlink(SEM_FILE1);
    sem_unlink(SEM_FILE2);
    sem_unlink(SEM_FILE3);
    sem_unlink(SEM_FILE4);

    fprintf(stderr, "Philosopher #%d completed %c cycles\n", n, m);
    printf("Caught signal %d\n", signum);
    exit(signum);
}

void eat(int n){
    printf("Philosopher #%d is eating", n);
}

void think(int n){
    printf("Philosopher #%d is thinking", n);
}

void wait2(sem_t* chopstick) {

    sem_wait(chopstick); // locks a semaphore
}

void signal2(sem_t* chopstick) {
    
    sem_post(chopstick); // unlocks a semaphore
}


// ps -aux | grep dining-p
// kill -TERM 'pid'