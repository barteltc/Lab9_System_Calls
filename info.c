/*
 * File: info.c
 * Assignment: Lab 9 - PC Information
 * Author: Bartelt, Chase
 * Section: 111
 * Date: 11/02/2026
 */
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>

static void displayClock(clockid_t clock, char *name);
static void displaySystem(void);

/**
 * Displays clock time in nanoseconds
 */
static void displayClock(clockid_t clock, char *name)
{
    struct timespec ts;

    if (clock_gettime(clock, &ts) == -1)
    {
        perror("clock_gettime failed");
        return;
    }

    long long nanoseconds =
        (long long)ts.tv_sec * 1000000000LL +
        ts.tv_nsec;

    printf("%s: %lld ns\n", name, nanoseconds);
}

/**
 *Displays operating system
 */
static void displaySystem(void)
{
    struct utsname systemInfo;
    if (uname(&systemInfo) == -1)
    {
        perror("uname failed");
        return;
    }

    if (systemInfo.sysname[0] != '\0')
    {
        printf("OS Name: %s\n", systemInfo.sysname);
    }
    if (systemInfo.release[0] != '\0')
    {
        printf("OS Release: %s\n", systemInfo.release);
    }

    if (systemInfo.version[0] != '\0')
    {
        printf("OS Version: %s\n", systemInfo.version);
    }

    if (systemInfo.machine[0] != '\0')
    {
        printf("Hardware: %s\n", systemInfo.machine);
    }
}

/**
 * Displays the system's network hostname
 */
static void displayHostname(void)
{
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("gethostname failed");
        return;
    }

    hostname[sizeof(hostname) - 1] = '\0';

    if (hostname[0] != '\0')
    {
        printf("Hostname:    %s\n", hostname);
    }
}

/**
 * Displays the number of available processors
 */
static void displayCPUs(void)
{
    int cpus = get_nprocs();

    if (cpus == -1)
    {
        perror("get_nprocs failed");
        return;
    }

    printf("CPUs:        %d\n", cpus);
}

/**
 * Displays total and available physical memory in bytes
 */
static void displayMemory(void)
{
    long totalPages = sysconf(_SC_PHYS_PAGES);
    long freePages = sysconf(_SC_AVPHYS_PAGES);
    int pageSize = getpagesize();

    if (totalPages == -1 || freePages == -1 || pageSize <= 0)
    {
        fprintf(stderr, "Failed to retrieve memory information\n");
        return;
    }

    unsigned long long totalMemory =
        (unsigned long long)totalPages * pageSize;

    unsigned long long freeMemory =
        (unsigned long long)freePages * pageSize;

    printf("Total Memory: %llu bytes\n", totalMemory);
    printf("Free Memory:  %llu bytes\n", freeMemory);
}

/**
 * Main method
 */
int main(void)
{
    displayClock(CLOCK_REALTIME, "CLOCK");
    displaySystem();
    displayHostname();
    displayCPUs();
    displayMemory();

    return 0;
}