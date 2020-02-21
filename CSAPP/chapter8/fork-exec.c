#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


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
    pid_t ret_pid;
    char *command = argv[1];
    char **command_args = &argv[1];
    // char **myargs = &argv[1];
    char *path = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    char *env[] = {path, NULL};

    if ( (ret_pid = Fork()) == 0)
    {
        printf("Running command %s\n", command);
        for (int i = 0; i < argc-1; i++)
        {
            printf("%s\n", command_args[i]);
        }
        execve(command, command_args, env);
    }
    else
    {
        printf("Waiting in parent\n");
        return 0;
    }

}