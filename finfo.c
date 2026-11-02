/*
 * File: finfo.c
 * Assignment: Lab 9 - File information
 * Author: Bartelt, Chase
 * Section: 111
 * Date: 11/02/2026
 */
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat fileInfo;

    if (argc != 2)
    {
        printf("Error: Please provide a filename\n");
        return 1;
    }

    if (stat(argv[1], &fileInfo) == -1)
    {
        perror("stat failed");
        return 1;
    }

    /**
     * Displays the file type
     */
    if (S_ISREG(fileInfo.st_mode))
    {
        printf("File Type: Regular file\n");
    }
    else if (S_ISDIR(fileInfo.st_mode))
    {
        printf("File Type: Directory\n");
    }
    else if (S_ISFIFO(fileInfo.st_mode))
    {
        printf("File Type: Named pipe\n");
    }
    else if (S_ISSOCK(fileInfo.st_mode))
    {
        printf("File Type: Socket\n");
    }
    else if (S_ISCHR(fileInfo.st_mode))
    {
        printf("File Type: Character device\n");
    }
    else if (S_ISBLK(fileInfo.st_mode))
    {
        printf("File Type: Block device\n");
    }
    else
    {
        printf("File Type: Other\n");
    }

    printf("File Size: %lld bytes\n", (long long)fileInfo.st_size);
    printf("Owner ID: %lu\n", (unsigned long)fileInfo.st_uid);

    /**
     * Displays file permissions
     */
    printf("Permissions: ");
    printf("%c", (fileInfo.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (fileInfo.st_mode & S_IXUSR) ? 'x' : '-');

    printf("%c", (fileInfo.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (fileInfo.st_mode & S_IXGRP) ? 'x' : '-');

    printf("%c", (fileInfo.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (fileInfo.st_mode & S_IXOTH) ? 'x' : '-');

    printf("\n");

    struct tm *modifiedTime = localtime(&fileInfo.st_mtime);
    if (modifiedTime == NULL)
    {
        perror("localtime failed");
        return 1;
    }

    char dateString[64];
    size_t result = strftime(
        dateString,
        sizeof(dateString),
        "%Y-%m-%d %H:%M:%S",
        modifiedTime);

    if (result == 0)
    {
        printf("Formatted string couldn't fit in array\n");
        return 1;
    }
    printf("Last Modified: %s\n", dateString);
    return 0;
}