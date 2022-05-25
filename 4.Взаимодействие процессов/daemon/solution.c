#define __GNU_SOURCE
#include <sys/types.h>  // fork
#include <unistd.h>     // pid_t, chdir, close
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>     // exit

/*
В задании требуется доработать демон, разработанный ранее в задании 6 
модуля 3.5. Задача -- снабдить демон обработчиком сигнала SIGURG, по приходу 
которого демон должен завершать свою работу
*/

#define PASS ((void)0)

void sighandler(int signum) {
    exit(EXIT_SUCCESS);
}


int main(void) {
    pid_t pid = fork();   
    
    if (pid == 0) {
        // daemon child
        chdir("/");
        pid_t new_pid = setsid();

        signal(SIGURG, sighandler);

        printf("%d\n", new_pid);
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);

        while (1)
            PASS;

    } else {
        // parent
        PASS;
    }
    
    return 0;

    /* Более красивый вариант
     *
    int pid = fork();
    if (pid) {
        printf("%d\n", pid);
        exit(0);
    }

    signal(SIGURG, exit);
    chdir("/");
    setsid();

    while (3 != pid)
    close(pid++);

    while(1) PASS;
    */
}

