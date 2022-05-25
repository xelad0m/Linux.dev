#include <signal.h>
#include <stdio.h>
#include <unistd.h>     // usleep
#include <stdlib.h>     // exit

/*
Разработать приложение, умеющее обрабатывать сигналы SIGUSR1 ,SIGUSR2, 
SIGTERM. После старта Ваше приложение должно по приходу одного из сигналов 
SIGUSR1,  SIGUSR2 выполнять суммирование числа срабатываний каждого из 
сигналов, а после прихода сигнала SIGTERM, требуется вывести в стандартный 
поток вывода 2 числа, разделенных пробелом, соответствующих количеству 
обработанных сигналов SIGUSR1, SIGUSR2, и завершить программу.
*/

#define INFINITE_LOOP while(1)


void sighandler(int sig) {
    static int sum1, sum2;

    sum1 += (sig == SIGUSR1);
    sum2 += (sig == SIGUSR2);

    if (sig == SIGTERM) {
        printf("%d %d\n", sum1, sum2);
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);
    signal(SIGTERM, sighandler);

    INFINITE_LOOP;
}

