#include <stdio.h>
#include "solution.h"

int main()
{
    int i = 0;          // переменная, хранит счетчик
    int * count = &i;   // указатель типа int, хранит ссылку на счетчик

    const char * sometext = "sometext 0";   // указатель на последовательность чаров

    int stats;

    stats = stringStat(sometext, 2, count);             // передается const char*, size_t, int*
    printf("Stats: %d, counter: %d\n", stats, *count);      // печатается int

    stats = stringStat(sometext, 3, count);
    printf("Stats: %d, counter: %d\n", stats, *count);

    return 0;
}
