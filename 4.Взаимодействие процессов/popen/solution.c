#include <stdio.h>
#include <stdlib.h>     // exit

/*
Некоторая утилита генерирует довольно большой вывод, а вам требуется 
всего-лишь посчитать количество символов '0' в этом выводе. Утилита при 
запуске принимает 1 параметр. Вам требуется разработать программу, которая 
вызывает указанную утилиту, с заданным параметром и подсчитывает количество 
символов '0' в ее выводе. Ваша программа принимает на вход 2 параметра - имя 
утилиты, в текущем каталоге и ее параметр. Ваша программа должна после 
подсчета вывести найденное число '0' в отдельной строке, заканчивающейся 
символом конца строки.

./solution echo 1011010100
5
*/

#define BUFSIZE 10
#define CMDSIZE 256

int main(int argc, const char **argv) 
{
    if (argc != 3) {
        printf("\n\tUsage: %s someprog param\n\n", argv[0]); 
        exit(EXIT_FAILURE);
    }
    
    char cmd[CMDSIZE];
    char buf[BUFSIZE];
    FILE *ptr;
    int counter = 0;
    int i;

    snprintf(cmd, CMDSIZE, "%s %s", argv[1], argv[2]);
    //printf("%s\n", cmd);


    if ((ptr = popen(cmd, "r")) != NULL) {
        while (fgets(buf, BUFSIZE, ptr) != NULL) {
            //printf("%s ", buf);
            for (i=0; buf[i]; i++) {
                if (buf[i] == '0')      // Ну дела! Тут не "", а СТРОГО '' !!!
                    counter++;
            }
            //printf("%d\n", counter);
        }
        (void) pclose(ptr);
    }

    printf("%d\n", counter);

    return 0;
}
