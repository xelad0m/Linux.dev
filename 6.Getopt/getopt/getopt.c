#include <unistd.h>     // getopt
#include <getopt.h>     // getopt_long
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int c, char **v) {

    int is_brackets = 0;
    int opindex = 0;
    int opchar = 0;
    char string[] = "Und wenn du lange in einen Abgrund blickst, blickt der Abgrund auch in dich hinein";
    int length = 0;

    // массив структур
    struct option opts[] = { 
        // в is_brackets будет записано 1 если есть такая опция
        {"brackets", no_argument, &is_brackets, 1},
        
        // только с аргументом, значение будет браться из getopt()
        {"length", required_argument, 0, 'l'},

        // longname option
        {"authornameshouldbeprinted", no_argument, 0, 'a'},
        
        {0, 0, 0, 0}, // так прост обозначается конец массива структур

    };

    // разбор параметров ком.стр.
    // - формат "bl:aq" значит у l есть параметр, у остальных нет, q значит 
    //   какая-то несуществующая опция
    //   :: значит необязательный параметр
    // - массив аргументов
    // - индекс опции в командной строке (нужно, если порядок опций важен)
    while ( -1 != (opchar = getopt_long(c, v, "bl:aq", opts, &opindex)) )
    {   // для каждой опции вызывается разборщик getopt_long()
        switch ( opchar )
        {
            case 0: // 0 если опция нашлась в массиве структур, и она уже привязана к переменной (как 'brackets')
                    // тогда этой опции присваивается указанное в массиве структур значение
                printf("0\n");  // обозначить в консоли, что выполняется тут
                break;

            case 'l': // если опция нашлась не привязанная к переменной, то getopt()
                      // возвращает указанное в массиве структур значение, и его обработка идет уже тут
                length = atoi(optarg);
                printf("length=%d\n", length);
                break;

            case 'a':
                printf("(c) Friedrich Nietzsche\n");
                break;

            default: // добавили, чтоб посмотреть, что будет если встретится неизвестная опция
                printf("opchar: %c\n", opchar);

        }
    }

    if ( strlen(string) > length && 0 != length ) 
        string[length] = '\0';  // если в опция обрезка длина, то добавить конец строки
    
    if (is_brackets)
        printf("[%s]\n", string);
    else
        printf("%s\n", string);

    printf("Done\n");

}

