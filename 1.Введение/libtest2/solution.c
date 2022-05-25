#include <stddef.h>     // NULL
#include <stdbool.h>    // true, false
#include <stdio.h>      // printf, sprintf
#include <string.h>     // strcat
#include <stdlib.h>     // atoi
#include <dlfcn.h>      // dlopen, dlsym

// указатель на функцию, принимающую int возвращает int
typedef int (*some_linked_func) (int);    

union {
    some_linked_func f;
    void *p;
} fu;


bool init_library(char * libName, char * funcName) 
{
    // загрузка либы, режим - при обращении к функции
    char strLib[64] = {0}; // инициализируем массивом из 1 эл-та 0, т.е. концом строки  
    //snprintf(strLib, 64, "./%s", libName); // по указателю форматированные чары
    strcpy(strLib, "./");               // или так
    strcat(strLib, libName);            // .. плюс так

    void *handler = dlopen(strLib, RTLD_LAZY);  
    

    if (NULL == handler) // йода-нотация, исключает ошибку вида if(hdl=NULL)
        return false;

    // приведение типа указателя к нужному
    fu.p = dlsym(handler, funcName);
    
    if (NULL == fu.p)
        return false;

    return true;
}

int main(int argc, char* argv[])    // аргументы передаются уот так уот
{
    char * libName = argv[1];
    char * funcName = argv[2];
    char * param = argv[3];

    int par = atoi(param);
    
    //for (int i=0; i<argc; i++) {
    //    printf("%s\n", argv[i]);
    //}

    if ( init_library(libName, funcName) ) 
        printf("%d\n", fu.f(par));

    return 0;
}
