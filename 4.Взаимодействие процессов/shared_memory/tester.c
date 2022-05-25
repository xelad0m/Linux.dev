#include <stdio.h>
#include <sys/ipc.h>    // ftok
#include <sys/shm.h>

#define SHM_SIZE 1000
#define NUM_INTS 100

int main(int c, char ** v) {
    // ключ региона, по которому можно получить id региона
    const key_t key1 = ftok(v[0], 0); 
    // id региона
    const int shm_id1 = shmget(key1, SHM_SIZE, 
                               IPC_CREAT | 0666);
    // все прекрасно работает и через IPC_PRIVATE с передачей shmid региона,
    // но тут под проверялку нужен именно ключ региона
    const key_t key2 = ftok(v[0], 1);
    const int shm_id2 = shmget(key2, SHM_SIZE, 
                              IPC_CREAT | 0666);

    if ( (shm_id1 == -1) || (shm_id2 == -1)) {
        fprintf(stderr, "shmget() error\n");
        return 1;
    }
    
    int * shm_buf1;             // будем хранить инты
    int * shm_buf2;
    
    shm_buf1 = (int *) shmat(shm_id1, NULL, 0);    // указатель на начало 
    shm_buf2 = (int *) shmat(shm_id2, NULL, 0);    // указатель на начало 
    
    int i;
    for (i=0; i<NUM_INTS; i++) {
        *shm_buf1 = i;                  // пишем
        *shm_buf2 = NUM_INTS - i;

        shm_buf1++;                     // двигаем указатель на (int *)
        shm_buf2++;
    }

    // пауза
    printf("\n%d %d\n", key1, key2);
    printf ("Press <Enter> to exit...");
    fgetc (stdin);

    // освободить разделяемую память
    shmdt (shm_buf1);
    shmctl (shm_id1, IPC_RMID, NULL);
    
    shmdt (shm_buf2);
    shmctl (shm_id2, IPC_RMID, NULL);

    return 0;
}
