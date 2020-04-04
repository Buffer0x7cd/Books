#include "csapp.h"

void sigint_handler(){
    Sio_puts("Caught Signal SIGINT");
    _exit(0);
}

int main(){
    if (signal(SIGINT, sigint_handler) ==  SIG_ERR)
        unix_error("Error while installing the error");

    pause();

    return 0;
}