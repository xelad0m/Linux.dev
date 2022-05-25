#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>     // usleep

#define STACK_SIZE 10000
char child_stack[STACK_SIZE];


int child(void * params) {
    int c = 0;
    while (true) {
        usleep(500000);
        printf("child turn %d\n", c++);
    }
}


int main(void) {
    int c = 0;
    //int result = clone(child, child_stack + STACK_SIZE - 1, 0, 0);
    int result = clone(child, child_stack + STACK_SIZE - 1, CLONE_PARENT, 0);
    printf("clone result = %d\n", result);

    while (true) {
        usleep(500000);
        printf("parent turn %d\n", c++);
    }
    
}
