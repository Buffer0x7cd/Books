#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define N 10

pid_t Fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error, while calling fork\n");
        exit(EXIT_FAILURE);
    }
    return pid;
}

int main(int argc, char *argv[])
{
    pid_t pid[N], ret;
    int status;

    for (int i = 0; i < N; i++)
    {
        if ( (pid[i] = Fork()) == 0)
            exit(100+i);
    }

    int i = 0;
    int returncode; 

    while( (ret = waitpid(pid[i++], &status, 0)) > 0 )
    {
        if WIFEXITED(status)
        {
            printf("Child %d exited normally\n", ret);
        }
        else
        {
            printf("Child %d exited abnormally\n", ret);
        }
        
    }

    if (errno != ECHILD)
    {
        perror("Error while caling waitpid");
        exit(EXIT_FAILURE);
    }
    return 0;
}