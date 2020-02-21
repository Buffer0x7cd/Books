#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    pid_t child_pid;
    pid_t parent_pid;

    if ( (child_pid = fork()) == 0 )
    {
        printf("Exiting child process with pid %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Running Parent Process with id %d\n",getpid());
        while (1)
        ;
    }

    return EXIT_SUCCESS;
}