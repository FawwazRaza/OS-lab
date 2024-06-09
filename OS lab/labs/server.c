#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
 {

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666);
    if (shmid == -1) 
    {
        printf("error");
    }

    int *shm = (int *)shmat(shmid, NULL, 0);
    if (shm == (int *)-1)
    {
        printf("error");
    }

    int sum = shm[0];
    int count = shm[1];

    float avg = (float)sum / count;

    printf("sum = %d\n", sum);
    printf("avg = %f\n", avg);

    shmdt((void *)shm);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
