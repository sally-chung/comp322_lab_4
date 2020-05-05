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

sem_t *chopstick_0;
sem_t *chopstick_1;
int full_cycle;

void signal_handler(sem_t *chopstick[], int n, int m, int signum);
void eat(int phil_num);
void think(int phil_num);
void wait2(sem_t *chopstick);
void signal2(sem_t *chopstick);

int main(int argc, char *argv[])
{
    int full_cycle;

    int phil_num = strtol(argv[1], NULL, 10);

    chopstick_0 = sem_open(SEM_FILE0, O_CREAT | O_EXCL, 0666, 1);
    chopstick_1 = sem_open(SEM_FILE1, O_CREAT | O_EXCL, 0666, 1);


    printf("hello1\n");
    fflush(stdout);
    // signal(SIGTERM, signal_handler);

    /*
    while(1) {
        printf("Processing things #%d.\n", i);
        i++;
        sleep(1);
    }
*/

    do
    {
        printf("hello2\n");
        fflush(stdout);

        wait2(chopstick_0);

        printf("hello3\n");
        fflush(stdout);

        wait2(chopstick_1);

        printf("hello3\n");
        fflush(stdout);
        
        //eat for awhile
        eat(phil_num);
        // signal(SIGTERM, eat)
        
        printf("hello4");
        fflush(stdout);

        // signal(SIGTERM, signal_handler);
        signal2(chopstick_0);
        signal2(chopstick_1);
        // think for awhile
        think(phil_num);
    } while (true);

    return EXIT_SUCCESS;
}

// signal handler for SIGTERM when cmd 'kill -TERM pid' is called
void signal_handler(sem_t *chopstick[], int n, int m, int signum)
{
    sem_close(chopstick_0);
    sem_close(chopstick_1);

    sem_unlink(SEM_FILE0);
    sem_unlink(SEM_FILE1);

    fprintf(stderr, "Philosopher #%d completed %c cycles\n", n, m);
    printf("Caught signal %d\n", signum);
    exit(signum);
}

void eat(int phil_num)
{
    printf("Philosopher #%d is eating", phil_num);
    sleep(rand() % 5);
}

void think(int phil_num)
{
    printf("hello5");
    fflush(stdout);
    printf("Philosopher #%d is thinking", phil_num);
    sleep(rand() % 5);
}

void wait2(sem_t* chopstick)
{
    sem_wait(chopstick); // locks a semaphore
}

void signal2(sem_t* chopstick)
{

    sem_post(chopstick); // unlocks a semaphore
}

// ps -aux | grep dining-p
// kill -TERM 'pid'