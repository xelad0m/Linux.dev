#include <stdio.h>
#include <sys/ipc.h>        // ftok
#include <sys/shm.h>
#include <stdlib.h>         // atoi


/*
В системе существуют 2 региона разделяемой памяти, заполненной некоторыми 
числами (типа int). Каждый из регионов имеет размер 1000 байт. Вам требуется 
разработать приложение, которое попарно суммирует первые 100 чисел в этих 
регионах и помещает суммы в новый (созданный вашим приложением) регион памяти 
размером 1000 байт. Таким образом, после завершения работы Вашего приложения в
памяти должен существовать регион разделяемой памяти размером 1000 байт, 
содержащий в начале 100 сумм. Перед завершением работы приложение выводит в
стандартный поток ввода-вывода ключ созданного региона, завершающийся символом
конца строки. На вход ваше приложение принимает ключи существующих регионов 
памяти.
*/

#define SHM_SIZE 1000
#define NUM_INTS 100

int main(int c, char ** v) {
    
    if (c != 3) {
        printf("Usage: %s shmid1 shmid2\n", v[0]);
        return 0;
    }

    const key_t key = ftok(v[0], 0); // имя файла + чето еще = ключ IPC
    const int shmid = shmget(key, SHM_SIZE, IPC_CREAT|0660);

    printf("%d\n", key);

    const key_t key1 = atoi(v[1]);
    const int shmid1 =  shmget(key1, SHM_SIZE, 0); // флаги 0 -> существующий

    const key_t key2 = atoi(v[2]);
    const int shmid2 =  shmget(key2, SHM_SIZE, 0); // флаги 0 -> существующий
    
    // указатели на начало региона
    int * shm_buf = (int *) shmat(shmid, NULL, 0);
    int * shm_buf1 = (int *) shmat(shmid1, NULL, 0);
    int * shm_buf2 = (int *) shmat(shmid2, NULL, 0);

    int i;
    for (i=0; i<NUM_INTS; i++) {
        *shm_buf = *shm_buf1 + *shm_buf2;
        //printf(" | %d + %d = %d", *shm_buf1, *shm_buf2, *shm_buf);

        shm_buf++; shm_buf1++; shm_buf2++;
    }
    
    
    //shmdt(shm_buf); shmdt(shm_buf1); shmdt(shm_buf2);
    //shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
