#include "tux.h"
#include <time.h>
#include <string.h>
#include <sched.h>

#define toUpper(c) (c >= 'a' && c <= 'z')? (c - 'a' + 'A') : (c)

void printStuff(int);

int main(int argc, char** argv)
{
    long i, j;
    int sleep = 0, quantum = 0, letter = 0;
    char lastLetter;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
            sleep = 1;
        if (strcmp(argv[i], "-q") == 0)
            quantum = 1;
        if (strcmp(argv[i], "-l") == 0)
            letter = 1;
        lastLetter = argv[i][0];
    }

    struct timespec req;
    struct timespec rem;

    req.tv_sec = 0;
    req.tv_nsec = 1000000;

    sched_rr_get_interval(0, &rem);

    if (quantum)
        printf("time quantum: %ld sec, %ld nsec\n", rem.tv_sec, rem.tv_nsec);

    j = 0;
    for (i = 0; i < 5000000000; i++)
    {
        if (i % 100000000 == 0)
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
