#include "tux.h"

#define NLINES 7

void printSpaces(int spaces)
{
    int i;

    for (i = 0; i < spaces; i++)
    {
        printf(" ");
    }
}

void printTux(int spaces)
{
    int i;
    char* tux[NLINES] =
    {
        "     .--.",
        "    |o_o |",
        "    |:_/ |",
        "   //   \\ \\",
        "  (|     | )",
        " /'\\_   _/`\\",
        " \\___)=(___/",
    };

    printf("\n");

    for (i = 0; i < NLINES; i++)
    {
        printSpaces(spaces);
        printf("%s", tux[i]);
        printf("\n");
    }

    printf("\n");

    fflush(stdout);
}

void backtrackTux()
{
    int i;

    printf("\r");
    for (i = 0; i < NLINES + 2; i++)
    {
        moveUp();
    }
    fflush(stdout);
}

void moveUp()
{
    printf("\033[1A");
}
