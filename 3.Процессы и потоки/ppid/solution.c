/*
Разработать программу solution, которая осуществляет поиск родительского PID 
текущего процесса в файловой системе proc и выводит найденное значение на 
консоль.  Результат, возвращаемый функций должен быть выведен отдельной 
строкой(должен оканчиваться символом перевода строки \n) в stdio.

*/

#include <stddef.h>     // NULL
#include <stdio.h>
#include <stdlib.h>     // atoi
#include <unistd.h>     // pid_t
#include <limits.h>     // PATH_MAX
#include <fcntl.h>      // O_RDONLY


typedef struct {
    pid_t   pid;
    char    name[PATH_MAX];
    char    state[1];
    pid_t   ppid;
} stathead_t;


stathead_t get_parent_pid(pid_t current) {

    FILE * fd = NULL;
    char filename[PATH_MAX] = {0};
    stathead_t stat;

    snprintf(filename, sizeof(filename), "/proc/%d/stat", current);

    fd = fopen(filename, "r");
    if (NULL == fd) 
        fprintf(stderr, "Error: Couldn't open [%s]\n", filename);

    fscanf(fd, "%d %s %s %d", &stat.pid, stat.name, stat.state, &stat.ppid);

    return stat;
}

void print_process_parents(pid_t pid) {

    stathead_t stat;
    pid_t current = pid;
    
    printf("PID: %d\n", current);

    while (current != 1 ) {
        stat = get_parent_pid(current);
        printf("-> PPID: %d %s\n", stat.ppid, stat.name); 
        current = stat.ppid;
    }
}


int main(int c, const char **v) {
    pid_t pid = getpid();   // my PID
    stathead_t stat = get_parent_pid(pid);

    printf("%d\n", stat.ppid);
    
    
    return 0;
}

