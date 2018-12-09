#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include "tux.h"

#define SNAME           "/sharedsem"

#define TOTAL_TIME      5000000000
#define TIME_SLICE      100000000
#define MIL_SEC         1000000

#define toUpper(c)      (c >= 'a' && c <= 'z')? (c - 'a' + 'A') : (c)

extern int errno;

void printStuff(int);

int main(int argc, char** argv)
{
    long i, j;
    int sleep = 0, quantum = 0, letter = 0, sem = 0;
    char lastLetter;
    sem_t* s;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
            sleep = 1;
        if (strcmp(argv[i], "-q") == 0)
            quantum = 1;
        if (strcmp(argv[i], "-l") == 0)
            letter = 1;
        if (strcmp(argv[i], "-w") == 0)
            sem = 1;

        lastLetter = argv[i][0];
    }

    if (sem)
    {
        s = sem_open(SNAME, O_CREAT, O_RDWR, 1);
        if (errno)
        {
            printf("%s\n", strerror(errno));
            exit(1);
        }
        sem_getvalue(s, &sem);
        printf("value: %d\n", sem);
        sem_wait(s);
    }

    struct timespec req;
    struct timespec rem;

    req.tv_sec = 0;
    req.tv_nsec = MIL_SEC;

    sched_rr_get_interval(0, &rem);

    if (quantum)
        printf("time quantum: %ld sec, %ld nsec\n", rem.tv_sec, rem.tv_nsec);

    j = 0;
    for (i = 0; i < TOTAL_TIME; i++)
    {
        if (i % TIME_SLICE == 0)
        {
            j++;
            if (letter)
            {
                printf("_%c", toUpper(lastLetter));
                fflush(stdout);
            }
            else
            {
                printStuff(j);
            }

            if (sleep)
                nanosleep(&req, &rem);

            if (i > (long)TOTAL_TIME / (long)2 && sem)
            {
                sem_post(s);
                sem = 0; // make sure the semaphore is only posted to once
            }
        }
    }

    if (!letter)
        printTux(j);
    printf("done%c!\n", (letter)? toUpper(lastLetter) : '!');

    return 0;
}

void printStuff(int spaces)
{
    int i;
    printTux(spaces % 60);

    for (i = 0; i < spaces; i++)
    {
        printf("=");
    }
    backtrackTux();

    fflush(stdout);
}
