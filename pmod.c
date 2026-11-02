/*
 * File: pmod.c
 * Assignment: Lab 9 - Process modification
 * Author: Bartelt, Chase
 * Section: 111
 * Date: 10/29/2026
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(void)
{
    errno = 0;
    int nice10 = nice(10);

    // Error handling
    if (nice10 == -1 && errno != 0)
    {
        perror("Nice failed");
        return 1;
    }

    printf("Nice Value: %d\n", nice10);

    /**
     * Nanosleep
     */
    struct timespec duration;
    duration.tv_sec = 1;
    duration.tv_nsec = 837272638;

    if (nanosleep(&duration, NULL) == -1)
    {
        perror("nanosleep failed");
        return 1;
    }

    printf("Goodbye!\n");
    return 0;
}