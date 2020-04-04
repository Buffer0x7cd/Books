#include "csapp.h"

volatile sig_atomic_t pid;

void child_handler(int signum)
{
    int olderrno = errno;
    pid_t child_pid = waitpid(-1, NULL, 0);
    pid = child_pid;
    errno = olderrno;
}


int main(int argc, char **argv)
{
    sigset_t mask, prev;
    Sigemptyset(&mask);
    printf("Parent is running with PID:%d\n", getpid());
    Sigaddset(&mask, SIGCHLD);
    Signal(SIGCHLD, child_handler);
    Sigprocmask(SIG_BLOCK, &mask, &prev);
    if (Fork() == 0)
    {
        sleep(3);
        printf("Child with PID %d is exiting now\n", getpid());
        exit(0);
    }

    pid = 0;
    Sigprocmask(SIG_SETMASK, &prev, NULL);

    while(!pid)
        ;

    printf("PID is now %d\n", pid);
}
