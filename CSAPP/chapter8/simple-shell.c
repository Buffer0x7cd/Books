    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>

#define CMDLIST 127
#define MAXARGS 127


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

int parseline(char *buffer, char *argv[])
{
    int argc;
    char *delim;
    int bg;

    buffer[strlen(buffer) - 1] = ' ';
    while( *buffer && (*buffer == ' '))
        buffer++;

    argc = 0;
    while ( delim = strchr(buffer, ' '))
    {
        argv[argc++] = buffer;
        *delim = '\0';
        buffer = delim + 1;
        while ( *buffer && (*buffer) == ' ')
            buffer++;  
    }
    argv[argc] = NULL;
    if (argc == 0)
        return 1;
    
    if ( (bg = (*argv[argc-1] == '&') ) != 0 )
        argv[--argc] = NULL;

    return bg; 
}

int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "&"))
        return 1;
    
    return 0;
}

void eval(char cmdline[])
{
    char *argv[MAXARGS];
    char buffer[CMDLIST];
    int bg;
    char *environ[] = {NULL};

    pid_t pid;

    strcpy(buffer, cmdline);
    bg = parseline(buffer, argv);

    if (argv[0] == NULL)
        return;

    if (!builtin_command(argv)) 
    {
        pid = Fork();
        if (pid == 0)
            if(execve(argv[0], argv, NULL) < 0)
            {
                printf("Command %s not found\n", argv[0]);
                exit(0);
            }
    }

    if (!bg)
    {
        int status;
        if ( (waitpid(pid, &status, 0))  < 0)
        {
            perror("Error while waiting for the child process");
            exit(0);
        }
    }
    else
        printf("[%d]:%s", pid, cmdline);

    return 0;
}

int main(int argc, char *argv[])
{
    char cmdline[CMDLIST];

    while (1)
    {
        printf("sshell>");
        fgets(cmdline, CMDLIST, stdin);

        if (feof(stdin))
            exit(EXIT_SUCCESS);

        eval(cmdline);
    }

    return 0;    
}

