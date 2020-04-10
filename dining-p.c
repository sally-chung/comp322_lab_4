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

void eat();
void think();

int main(int argc, char* argv[]) {
    sem_t chopstick[5];
    unsigned int usecs;
    
    usecs = rand();

    do { 
        wait(chopstick[i]);
        wait(chopstick[(i+1)]);
        /* ...
        eat for awhile */
        signal(chopstick[i]);
        signal(chopstick[(i+1)]);
        /* ...
        think for awhile */
    } while(true);

}

void eat(unsigned int usecs){
    usleep(usecs);
    printf("Philosopher #%d is eating", number);
}

void think(unsigned int usecs){
    usleep(usecs);
    printf("Philosopher #%d is thinking", number);
}