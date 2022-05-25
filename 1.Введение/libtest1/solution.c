#include <stddef.h>     // size_t
//#include "solution.h"

int stringStat(const char *string, size_t multiplier, int *count) 
{
    int len = 0;

    (*count)++; // указатель разыменовывается и значение ++

    while (*string++ != '\0') { // указатель сдвигается ++ и разыменовывается
        len++;
    }

    return len * multiplier;
}
