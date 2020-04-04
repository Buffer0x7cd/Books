#include "csapp.h"

void child_handler(int signum)
{
    int olderrno = errno;
    pid_t child_pid;

    while ((child_pid = waitpid(-1, NULL, 0)) > 0)
        Sio_puts("Handler reaped Child\n");
    
    if (errno != ECHILD)
        Sio_error("waitpid error\n");
    sleep(1);
    errno = olderrno;
}


int main(void)
{
    char buffer[MAXBUF];

    if (signal(SIGCHLD, child_handler) == SIG_ERR)
        unix_error("signal error");

    for (int i = 0; i < 3; i++)
    {
        if (Fork() == 0){
            printf("Child with PID: %d running\n",getpid());
            sleep(1);
            exit(0);
        }
    }

    if (read(STDIN_FILENO, buffer, sizeof(buffer)) < 0)
        unix_error("Error while reading the buffer");
    
    printf("Parent process with PID %d is running\n", getpid());

    while(1);

    return 0;
}
