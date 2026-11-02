# Lab9_System_Calls

**CPE-2600 Systems Programming - System Calls**  
**Author:** Chase Bartelt

## Description

This lab explores commonly used POSIX system calls in C on a Linux operating system. It consists of four programs that retrieve system information, inspect processes, modify process behavior, and display file information.

## Features

### Info (`info.c`)

Displays information about the host PC, including:

- Current time in nanoseconds
- System hostname
- Operating system name
- Operating system release and version
- Hardware architecture
- Number of CPUs
- Total physical memory in bytes
- Available free memory in bytes

### Pinfo (`pinfo.c`)

Displays information about a specified process, including:

- Process ID (PID)
- Process priority
- Process scheduling method

If no PID is provided, the program displays information about its own process.

The program also handles invalid process IDs and incorrect command-line arguments.

### Pmod (`pmod.c`)

Demonstrates process modification using system calls.

- Adjusts its own process priority by increasing its nice value by 10
- Sleeps for 1,837,272,638 nanoseconds (approximately 1.84 seconds)
- Prints a goodbye message before exiting

### Finfo (`finfo.c`)

Displays information about a file specified through the command line.

- File type
- File permissions
- File owner (UID)
- File size in bytes
- Last modification date and time
- Error handling for invalid or inaccessible files

## Building the Program

The programs can be compiled using GCC or the provided Makefile.

**Using Make:**

```bash
make clean
make
```

**Compiling manually:**

Pinfo:
```bash
gcc -o pinfo pinfo.c -Wall -Wextra
```

Finfo:
```bash
gcc -o finfo finfo.c -Wall -Wextra
```

Info:
```bash
gcc -o info info.c -Wall -Wextra
```

Pmod:
```bash
gcc -o pmod pmod.c -Wall -Wextra
```

## Running the Programs

After compiling, run each program from the terminal.

**Info:**
```bash
./info
```

**Pinfo:**
```bash
./pinfo
./pinfo 1234
```

**Pmod:**
```bash
./pmod
```

**Finfo:**
```bash
./finfo info.c
```

## Supported Commands

| Command | Description |
|---|---|
| `make` | Compiles all four programs |
| `make clean` | Removes compiled files |
| `./info` | Displays system information |
| `./pinfo` | Displays current process information |
| `./pinfo <PID>` | Displays information for a specified process |
| `./pmod` | Modifies process priority and sleeps |
| `./finfo <filename>` | Displays information about a specified file |

## System Calls Used

| Program | System Calls / Functions |
|---|---|
| Info | `clock_gettime()`, `uname()`, `gethostname()`, `get_nprocs()`, `sysconf()`, `getpagesize()` |
| Pinfo | `getpid()`, `getpriority()`, `sched_getscheduler()` |
| Pmod | `nice()`, `nanosleep()` |
| Finfo | `stat()`, file metadata and permission utilities |

## Requirements

- Linux or Windows Subsystem for Linux (WSL)
- GCC compiler
- GNU Make
- POSIX-compatible environment

File information testing should be performed within the Linux filesystem rather than the Windows filesystem.

## Error Handling

The programs include error handling for situations such as:

- Invalid process IDs
- Nonexistent processes
- Missing or excessive command-line arguments
- Missing or inaccessible files
- Failed system calls

## Testing

Programs can be tested using different command-line arguments to verify normal operation and error handling.

Example tests:

```bash
./info
./pinfo
./pinfo 1
./pinfo -50
./pinfo hello
./pmod
./finfo info.c
./finfo nonexistent.txt
```

## Files

```text
Lab9_System_Calls/
├── info.c
├── pinfo.c
├── pmod.c
├── finfo.c
├── Makefile
├── .gitignore
└── README.md
```

## Course Information

**Course:** CPE-2600 Systems Programming  
**Assignment:** Lab 9 - System Calls  
**Semester:** Fall 2026  
**Author:** Chase Bartelt
