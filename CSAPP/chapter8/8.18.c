// Demo of waitpid function
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define N 3
pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("Error while performing fork");
        exit(0);
    }

    return pid;
}


int main(int argc, char **argv)
{
    int status, i;
    pid_t pid;

    for(i = 0; i < N; i++)
        if ((pid = Fork()) == 0)
            exit(100+i);
    
    while ((pid = waitpid(-1, &status, 0)) > 0 )
    {
        if (WIFEXITED(status))
            printf("Child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else
        {
            printf("Child %d exited abnoramlly exited\n", pid);
        }
        
    }

    if (errno != ECHILD)
        perror("waitpid error");


    exit(0);

}