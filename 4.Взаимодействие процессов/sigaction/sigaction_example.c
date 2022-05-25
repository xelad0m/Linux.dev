// signal не блокирует получение других сигналов пока выполняется текущий обработчик, он будет прерван и начнет
// выполняться новый обработчик

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <signal.h>

#include <unistd.h>

 

void signal_handler(int signal_number) {
    printf("\nCalled with %d\n", signal_number);
    exit(0);
}

 

int main() {
    int value = 0;

    struct sigaction act;
    memset(&act, 0, sizeof(act));

    act.sa_handler = signal_handler;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT); // block this signal when run handler
    act.sa_mask = set;
    sigaction(SIGINT, &act, 0);

    while (1) {
        printf("value = %d\n", value++);
        usleep(500000);

    }

    return EXIT_SUCCESS;
}
