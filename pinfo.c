/*
 * File: pinfo.c
 * Assignment: Lab 9 - Process information
 * Author: Bartelt, Chase
 * Section: 111
 * Date: 11/02/2026
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/resource.h>
#include <sched.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    char *endptr;
    /**
     * Process ID selection and input validation
     */
    if (argc == 2)
    {
        // Convert PID string to number
        errno = 0;
        /*
         * Convert command-line PID from a decimal string.
         * endptr identifies where numeric conversion stopped.
         * Reject invalid characters and out-of-range values.
         */
        long result = strtol(argv[1], &endptr, 10);

        // Input Validation
        if (endptr == argv[1] || *endptr != '\0')
        {
            printf("Invalid PID\n");
            return 1;
        }
        if (result <= 0)
        {
            printf("Invalid PID\n");
            return 1;
        }
        if (errno == ERANGE || result > INT_MAX)
        {
            printf("Invalid PID\n");
            return 1;
        }
        // Assigning temp variable to pid
        pid = (pid_t)result;
    }

    else if (argc == 1)
    {
        // If no input, assign it
        pid = getpid();
    }
    else
    {
        // More input validation
        printf("Too many inputs\n");
        return 1;
    }

    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0)
    {
        perror("getpriority failed");
        return 1;
    }

    /**
     * Scheduler
     */
    int scheduler = sched_getscheduler(pid);

    if (scheduler == -1)
    {
        perror("sched_getscheduler failed");
        return 1;
    }

    /**
     * Display scheduling policy
     */
    switch (scheduler)
    {
    case SCHED_OTHER:
        printf("Scheduler: SCHED_OTHER\n");
        break;

    case SCHED_FIFO:
        printf("Scheduler: SCHED_FIFO\n");
        break;

    case SCHED_RR:
        printf("Scheduler: SCHED_RR\n");
        break;

    case SCHED_BATCH:
        printf("Scheduler: SCHED_BATCH\n");
        break;

    case SCHED_IDLE:
        printf("Scheduler: SCHED_IDLE\n");
        break;

    default:
        printf("Scheduler: Unknown\n");
        break;
    }

    // Print statement
    printf("Priority: %d\n", priority);
    printf("Process ID: %ld\n", (long)pid);
    return 0;
}