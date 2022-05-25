#include <signal.h>
#include <stdio.h>
#include <unistd.h>     // usleep



void mysignal_handler(int signalno) {
    printf("Called with sig.No %d\n", signalno);
}


int main() {
    int c=0;

    // Не используйте эту функцию (man 2 signal)
    signal(SIGINT, mysignal_handler);   // назначаем обработчик на SIGINT

    while(1){
        printf("Hello %d\n", c++);
        usleep(500000);
    }

    return 0;
}

