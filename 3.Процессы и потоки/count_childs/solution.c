#include <stddef.h>     // NULL
#include <stdio.h>
#include <stdlib.h>     // atoi
#include <string.h>     // strtok
#include <unistd.h>     // pid_t
#include <limits.h>     // PATH_MAX
#include <fcntl.h>      // O_RDONLY

/*
Разработать программу solution, которая по заданному pid, осуществляет поиск 
всех потомков (все уровни родства) процесса с этим идентификатором и выводит 
их количество (включая процесс с заданным pid).

- список всех потомков procfs хранит в /proc/PID/task/PID/children
*/


#define SIZE 2048

void count_childs(pid_t current, int * count);


void split(char *str, const char *delim, int * counter) {  
    char * pid_str;
    char * rest = str;
    
    // strtok не подходит для рекурсиных вызовов, т.к. хранит &rest в static
    while ( (pid_str = strtok_r(rest, delim, &rest)) ) {
        (*counter)++;   // на каждом ненулевом PID
        count_childs((pid_t)atoi(pid_str), counter);
    }
}


void count_childs(pid_t current, int * counter) {

    FILE * fd = NULL;
    char filename[PATH_MAX] = {0};
    char pids_string[SIZE];

    snprintf(filename, sizeof(filename), "/proc/%d/task/%d/children", current, current);

    if((fd = fopen(filename, "r")) != NULL) {  
        fgets(pids_string, SIZE, fd);
        fclose(fd);
    }
   
    // если список потомков не пустой
    if (strcmp(pids_string, "")) {
        //printf("PIDS: %s\n", pids_string);
        const char * delim = " ";
        split(pids_string, delim, counter);
    }
}

int main(int c, const char **v) {

    pid_t pid = (c==2) ? (pid_t) atoi(v[1]) : getpid();
    int counter = 1;

    count_childs(pid, &counter);
    printf("%d\n", counter);

    return 0;
}



