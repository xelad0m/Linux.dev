#include <stddef.h>     // NULL
#include <stdbool.h>    // true, false
#include <stdio.h>      // printf
#include <dlfcn.h>      // dlopen, dlsym

//#include "hello.h" // при дин.линковке тоже не нужно

void (*hello_message)(const char *);    // nullptr

bool init_library() {
    // загрузка либы, режим - при обращении к функции
    void *handler = dlopen("./libHello.so", RTLD_LAZY);  

    if (NULL == handler) // йода-нотация, исключает ошибку вида if(hdl=NULL)
        return false;

    // приведение типа указателя к нужному (не обязательно)
    //hello_message = (void (*)(const char *)) dlsym(handler, "hello_message");
    hello_message = dlsym(handler, "hello_message");
    
    if (NULL == hello_message)
        return false;

    return true;
}

int main()
{
    if ( init_library() )
        hello_message("Noname");
    else
        printf("Library was not loaded\n");

    return 0;
}

