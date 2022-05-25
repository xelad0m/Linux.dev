#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>         // read
#include <string.h>         // strncmp
#include <stdlib.h>         // atoi, qsort

/*
Разработайте TCP сервер, предназначенный для сортировки символов в строке. 
Сервер получает на вход строки, оканчивающиеся символом '\0', сортирует в них 
символы в порядке убывания ASCII-кодов и отсылает обратно на клиент, в виде 
строки заканчивающейся '\0'. Завершение работы сервера происходит после 
получения строки, содержащей только 'OFF'. 

При старте сервер получает на вход номер порта в качестве параметра командной 
строки. bind производится на адресе 127.0.0.1
*/


struct sockaddr_in local;   // 'глобальная' структура для адреса сети


int compare(const void * a, const void * b) {
    return (*(char *) b - *(char *) a); // УБЫВАНИЕ
}


int server(int port) {
    
    // по протоколу TCP - сокет для запросов на установление соединение
    int ss = socket(AF_INET, SOCK_STREAM, 0); // (ipv4, TCP, вариант протокола)
    // клиентский сокет - для самих соединений
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr); // строку в адрес и в структуру
    local.sin_port = htons(port);            // порядок байт (узловой -> сетевой)
    local.sin_family = AF_INET;

    // для серверного сокета bind остается (чтоб слушать нужен конкретный порт)
    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);  // драйвер протокола TCP начинает слушать (сокет, размер очереди)
    
    // соединение одобрено, возвращает новый сокет для передачи данных
    cs = accept(ss, NULL, NULL); // (сокет, адрес клиента, длина адреса клиента)
                                 // адреса - как они сами передадут, тут нам оно не надо
    
    const char * off = "OFF\n";  // \n добавить по вкусу
    while (1) {
        // читаем из клиентского сокета то, что клиент прислал
        char buf[BUFSIZ];
        int len = read(cs, buf, BUFSIZ);
        
        // (клиент закрыл соединение)||(клиент просится на выход)
        if ( (len == 0) || (strncmp(buf, off, len) == 0) ) 
            break;

        qsort(&buf, len - 1, sizeof(char), compare); // без последнего символа, но это дело вкуса
        // если без сортировки, то просто эхо-сервер
        write(cs, buf, len);
    }

    return close(cs);

}


int main(int c, char ** v) {
 
    if (c != 2) {
        return printf("Usage: %s port", v[0]);
    }

    server(atoi(v[1]));

    return 0;

}
