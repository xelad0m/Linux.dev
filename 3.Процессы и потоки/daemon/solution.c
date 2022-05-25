#define __GNU_SOURCE
#include <sys/types.h>  // fork
#include <unistd.h>     // pid_t, chdir, close
#include <stdio.h>      // stdout ...


#define noop ((void)0)

int main(void) {
    pid_t pid = fork();   

    if (pid == 0) {
        // daemon child
        chdir("/");
        pid_t new_pid = setsid();
        printf("%d\n", new_pid);
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);

        while (1)
            noop;

    } else {
        // parent
        noop;
    }
    
    return 0;
}

