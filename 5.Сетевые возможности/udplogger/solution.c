#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>         // read
#include <stdlib.h>         // exit
#include <string.h>         // strncmp

/*
Разработайте UDP сервер для логирования (сбора и записи) сообщений. Сервер при
запуске принимает параметр -- номер порта, на котором будут приниматься 
запросы. Каждый запрос приходящий к серверу - строка, не превышающая размер 
5K. Задача сервера -- выводить приходящие строки в стандартный поток 
ввода-вывода, завершающиеся символом конца строки.

Сервер завершает работу, когда получает строку содержащую только текст 'OFF', 
и заканчивающуюся символом перевода строки '\n'. 

Сервер использует локальный адрес 127.0.0.1
*/


struct sockaddr_in local;   // структура для адреса сети


int main(int c, char ** v) {
    
    if (c != 2) {
        return printf("Usage: %s port\n", v[0]);
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);  // ipv4, дaтаграмма (т.е. UDP), вариант протокола

    inet_aton("127.0.0.1", &local.sin_addr); // строку в адрес и в структуру
    local.sin_family = AF_INET;

    local.sin_port = htons(atoi(v[1]));      // порядок байт (узловой -> сетевой)

    // 'открытие' порта
    bind(s, (struct sockaddr*) &local, sizeof(local));

    const char * off = "OFF\n";
    while (1) {
        char buf[BUFSIZ];
        int length = read(s, buf, BUFSIZ);
        buf[length] = '\0';

        if ( 0 == strcmp(buf, off) ) {
            exit(EXIT_SUCCESS);
        } else {
            printf("%s\n", buf);
        }
    }

    return 0;
}
