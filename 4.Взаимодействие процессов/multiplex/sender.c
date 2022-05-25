#include <stdio.h>
#include <fcntl.h>      // open
#include <stdlib.h>     // atoi, srand, rand
#include <time.h>       // time
#include <unistd.h>     // write


int main(int c, char ** v) {
    int out1 = open("./in1", O_RDWR); 
    int out2 = open("./in2", O_RDWR); 

    if (c != 2) {
        printf("Use: %s sum\n", v[0]);
        return 0;
    }
    
    int sum = atoi(v[1]);
    int inter_sum = 0;
    int ssum = 0;

    srand(time(NULL));
    
    while (inter_sum < sum) {
        int r = rand() % 10;                    // rand int in [0, 9]
        inter_sum = inter_sum + r;
        if (inter_sum > sum)
            r = r - inter_sum + sum;            // остаток до заданной суммы
        ssum = ssum + r;

        int ch = rand() % 3;                    // rand int in [0, 2] 
        
        char bytes[10];
        sprintf(bytes, "%d", r);                // itoa (adds '\0')
        //printf("-> %s\n", bytes);

        if (ch == 0) {                          // случайный канал 1:3
            write(out1, &bytes, sizeof(r));
            printf("%s", bytes);
        } else {
            write(out2, &bytes, sizeof(r));
            printf("[%s]", bytes);
        }
        usleep(1000);                           // иначе пропадают данные
    }

    printf("\nSent: %d\n", ssum);
    
    close(out1);
    close(out2);

    return 0;

}
