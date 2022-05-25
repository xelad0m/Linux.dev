#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>         // read
#include <string.h>         // strlen

struct sockaddr_in local;   // 'глобальная' структура для адреса сети

int server() {
    
    // по протоколу TCP - сокет для запросов на установление соединение
    int ss = socket(AF_INET, SOCK_STREAM, 0); // (ipv4, TCP, вариант протокола)
    // клиентский сокет - для самих соединений
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr); // строку в адрес и в структуру
    local.sin_port = htons(1234);            // порядок байт (узловой -> сетевой)
    local.sin_family = AF_INET;

    // для серверного сокета bind остается (чтоб слушать нужен конкретный порт)
    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);  // драйвер протокола TCP начинает слушать (сокет, размер очереди)
    
    // соединение одобрено, возвращает новый сокет для передачи данных
    cs = accept(ss, NULL, NULL); // (сокет, адрес клиента, длина адреса клиента)
                                 // адреса - как они сами передадут, тут нам оно не надо

    // читаем из клиентского сокета то, что клиент прислал
    char buf[BUFSIZ];
    read(cs, buf, BUFSIZ);
    printf("%s\n", buf);
    close(cs);

}

int client() {

    int s = socket(AF_INET, SOCK_STREAM, 0); // (ipv4, TCP, вариант протокола)

    inet_aton("127.0.0.1", &local.sin_addr); // строку в адрес и в структуру
    local.sin_port = htons(1234);            // порядок байт (узловой -> сетевой)
    local.sin_family = AF_INET;

    // bind не обязательно, привязка к порту произойдет автоматически
    // сокет (s) 'соединяется' с сервером (структурка local)
    connect(s, (struct sockaddr*) &local, sizeof(local));

    char buf[BUFSIZ] = "Hello\n";
    write(s, buf, strlen(buf) + 1);

}

int main(int c, char ** v) {
 
    if (c != 2) {
        return printf("Usage: %s [s(erver) | c(lient)]\n", v[0]);
    }

    if (v[1][0] == 's') {
        server();
    }

    if (v[1][0] == 'c') {
        client();
    }

    return 0;

}
