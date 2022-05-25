#include <stdio.h>          // есть хоть какая логика куда распихоны функции?
#include <sys/select.h>     // fd_set, FD_*, select
#include <sys/time.h>       // timeval
#include <unistd.h>         // read, usleep
#include <fcntl.h>          // open, O_*

/*
В текущем каталоге есть 2 канала in1 in2, в которые в случайном порядке 
поступают числа, которые необходимо просуммировать и вывести окончательную 
сумму на экран. Сумма выводится в отдельной строке, завершающейся символом 
конца строки. Признаком окончания подачи символов в каналы является закрытие 
этих каналов посылающей стороной.

Подсказка: для неблокирующего чтения использовать select.
Замечание: потокол обмена по каналу текстовый, то есть числа представлены 
строками (без разделителей. т.е. нужна просто сумма цифор)
*/

#define BUFSIZE 8 + 1 
#define CMDSIZE 256

int read_and_sum(int fd, int * sum) {
    char buf[BUFSIZE];
    int i;

    int bytes = read(fd, buf, BUFSIZE - 1);

    if (bytes > 0) {

        for (i = 0; buf[i] != '\0'; ++i) {
            int ctoi =  (int)buf[i] - (int)'0';     // ну а как еще?
            *sum = *sum + ctoi;
        }
        
        return bytes;

    } else {        // (bytes == 0) || (bytes == -1)
        return 0;   // (канал закрыт) или (ошибка чтения)
    }

}


int main(/* int argc, const char **argv */) 
{
    int in1 = open("./in1", O_RDONLY);
    int in2 = open("./in2", O_RDONLY);
    int sum = 0;

    if (! (in1 && in2)) {
        printf("Error with opening pipes\n");
        return 0;
    }
    
    int is_open1 = 1;
    int is_open2 = 1;

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 500;

    fd_set read_set;

    while (is_open1 || is_open2) {
        
        FD_ZERO(&read_set);     // обнулить готовность каналов

        FD_SET(in1, &read_set);
        FD_SET(in2, &read_set);
    
        // признаком закрытия канала будет снятие блокировки в select
        // и при этом прочитанные 0 байт (это штатная работа)
        int result = select(in2 + 1, &read_set, NULL, NULL, &timeout);

        if (result) {
            if ( FD_ISSET(in1, &read_set) ) {
                is_open1 = read_and_sum(in1, &sum);
            }
            if ( FD_ISSET(in2, &read_set) ) {
                is_open2 = read_and_sum(in2, &sum);
            }
        }
    }
    
    close(in1);
    close(in2);

    printf("%d\n", sum);

    return 0;
}
