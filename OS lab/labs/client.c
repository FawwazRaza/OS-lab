#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h> 

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("error");
        return 1; 
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) 
    {
        printf("error");
        return 1;
    }

    int sum = 0, count = 0, num;
    while (read(fd, &num, sizeof(int)) == sizeof(int)) 
    {
        sum += num;
        count++;
    }

    close(fd); 
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) 
    {
        printf("error");
        return 1; 
    }

    int *shm = (int *)shmat(shmid, NULL, 0);
    if (shm == (int *)-1) 
    {
        printf("error");
        return 1; 
    }

    shm[0] = sum;
    shm[1] = count;

    printf("data sent\n");

    return 0;
}
