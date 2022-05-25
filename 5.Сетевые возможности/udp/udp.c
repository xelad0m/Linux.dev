#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>         // read


struct sockaddr_in local;   // структура для адреса сети
                            // такое объявление эквивалентно static внутри функции
                            // суть в том, что оно создаются 1 раз и инициализируется нулями
                            // хранятся в .data (если инициализированы вручную) 
                            // или .bss (как здесть, неинициалированные)

int main(int c, char ** v) {
    
    int s = socket(AF_INET, SOCK_DGRAM, 0);  // ipv4, дaтаграмма (т.е. UDP), вариант протокола
    printf("socket=%d\n", s);                // дескриптор (сокета)

    inet_aton("127.0.0.1", &local.sin_addr); // строку в адрес и в структуру
    local.sin_port = htons(1234);            // порядок байт (узловой -> сетевой)
    local.sin_family = AF_INET;

    // "открытие" порта
    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    printf("%d\n", result);

    char buf[BUFSIZ];
    read(s, buf, BUFSIZ);
    printf("%s\n", buf);
    printf("bye\n");

    return 0;
}
