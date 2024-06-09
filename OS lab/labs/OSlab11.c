#include <sys/mman.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* foo(void *arg) 
{
    char *arr = (char *)arg;
    int half = 50;

    for (int i = 0; i < half; i++) 
    {
        if (arr[i] >= 'a' && arr[i] <= 'z') 
        {
            arr[i] = arr[i] - 'a' + 'A';
        } 
        else if (arr[i] >= 'A' && arr[i] <= 'Z') 
        {
            arr[i] = arr[i] - 'A' + 'a';
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
  
    int fd = open(argv[1], O_RDWR);
   
    char *arr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   

    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, foo, arr) != 0) 
    {
        printf("error ");
        munmap(arr, 100);
        close(fd);
        return 1;
    }

    if (pthread_create(&thread2, NULL, foo, arr + 50) != 0)
    {
        printf("error");
        pthread_cancel(thread1);
        munmap(arr, 100);
        close(fd);
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    munmap(arr, 100);
    close(fd);

    return 0;
}
