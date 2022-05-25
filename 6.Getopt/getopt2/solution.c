#include <unistd.h>     // getopt
#include <getopt.h>     // getopt_long
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Требуется написать программу solution, выполняющую разбор опций командной 
строки и выводящую в стандартный поток вывода символ '+', если набор 
корректен,или '-' в противном случае.

Описание возможных опций:
-q | --query (опциональный, но обязательно требует аргумента)
-i | --longinformationrequest (опциональный)
-v | --version (опциональный)
*/

int main(int c, char **v) {

    int opindex = 0;
    int opchar = 0;
    int corr = 0;

    // массив структур
    struct option opts[] = { 
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}, 
    };

    while ( -1 != (opchar = getopt_long(c, v, "q:iv", opts, &opindex)) )
    {   // для каждой опции вызывается разборщик getopt_long()
        switch ( opchar )
        {
            case 0:                
                //printf("opchar: %c\n", opchar);
                break;

            case 'q':                
                //printf("opchar: %c\n", opchar);
                break;

            case 'i':
                //printf("opchar: %c\n", opchar);
                break;
            
            case 'v':
                //printf("opchar: %c\n", opchar);
                break;

            default: {
                //printf("default opchar: %c\n", opchar);
                corr = -1;
                }
                break;

        }
    }

    printf("%c\n", (corr == 0) ? '+' : '-');
    
    return 0;
}

