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

sem_t *chopstick_0;
sem_t *chopstick_1;
int full_cycle;

void signal_handler(int phil_num, int full_cycle, int signum);
void eat(int phil_num);
void think(int phil_num);
void wait2(sem_t *chopstick);
void signal2(sem_t *chopstick);

int main(int argc, char *argv[])
{
    int full_cycle;
    full_cycle = 0;

    int value;

    int i;
    i = 0;

    int phil_num = strtol(argv[1], NULL, 10);

    chopstick_0 = sem_open(SEM_FILE0, O_CREAT, 0666, 1);
    chopstick_1 = sem_open(SEM_FILE1, O_CREAT, 0666, 1);

    sem_getvalue(chopstick_0, &value);
    printf("value: %d\n", value);

    do {
        wait2(chopstick_0);
        wait2(chopstick_1);

        //eat for awhile
        eat(phil_num);

        signal2(chopstick_0);
        signal2(chopstick_1);
        
        // think for awhile
        think(phil_num);
        i++;
        full_cycle++;

    } while (i < 2);

    signal_handler(phil_num, full_cycle, 5);

    sem_close(chopstick_0);
    sem_close(chopstick_1);

    sem_unlink(SEM_FILE0);
    sem_unlink(SEM_FILE1);

    return EXIT_SUCCESS;
}

// signal handler for SIGTERM when cmd 'kill -TERM pid' is called
void signal_handler(int phil_num, int full_cycle, int signum)
{
    fprintf(stderr, "Philosopher #%d completed %d cycles\n", phil_num, full_cycle);
    exit(signum);
}

void eat(int phil_num)
{
    printf("Philosopher #%d is eating\n", phil_num);
    sleep(rand() % 5);
}

void think(int phil_num)
{
    printf("Philosopher #%d is thinking\n", phil_num);
    sleep(rand() % 5);
}

void wait2(sem_t *chopstick)
{
    sem_wait(chopstick); // locks a semaphore
}

void signal2(sem_t *chopstick)
{

    sem_post(chopstick); // unlocks a semaphore
}

// ps -aux | grep dining-p
// kill -TERM 'pid'