#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>

int main(){


    sem_t *sem;

    int buffer[100];


    sem = sem_open("/my_semaphore3", 0, 0644, 1);




    if(sem==SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_wait(sem);
    printf("Process 3 Running\n");

      int infile = open("file1.txt", O_RDWR);
      char *a;
      char store[30];
      int rbytes;
      int count=0;

    while(read(infile, &store[count], sizeof(store[0]))>0){
        count++;
    }


    int countint =  atoi(&store[count-2]);
    int sum = atoi(&store[count-5]);

    double avg = sum/countint;

    char str[2];
        sprintf(str, "%d", count);

        char spac = ' ';
        write(infile, &spac, sizeof(char));
        write(infile, str, sizeof(str));


        printf("Process 3 Done\n");
        sem_close(sem);

    return 0;

}
