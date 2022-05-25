#include <stddef.h>     // NULL
#include <stdbool.h>    // true, false
#include <stdio.h>      // printf
#include <dlfcn.h>      // dlopen, dlsym

//#include "hello.h" // при дин.линковке тоже не нужно

// вариант вызова функций из динамических библиотек
typedef void (*hello_message)(const char *);    

union {
    hello_message f;
    void *p;
} fu;


bool init_library() {
    // загрузка либы, режим - при обращении к функции
    void *handler = dlopen("./libHello.so", RTLD_LAZY);  

    if (NULL == handler) // йода-нотация, исключает ошибку вида if(hdl=NULL)
        return false;

    // приведение типа указателя к нужному
    fu.p = dlsym(handler, "hello_message");
    
    if (NULL == fu.p)
        return false;

    return true;
}

int main()
{
    if ( init_library() )
        fu.f("Noname");
    else
        printf("Library was not loaded\n");

    return 0;
}

