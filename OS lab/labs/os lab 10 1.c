#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>

int main(){


    sem_t *sem;

    sem_t *sem2;
    int buffer[100];


    sem = sem_open("/my_semaphore2", 0, 0644, 1);
        sem2 = sem_open("/my_semaphore3", 0, 0644, 0);




    if(sem==SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    
    printf("Process 2 Running\n");

      int infile = open("file1.txt", O_RDWR);
      char a;
      int rbytes;
      int count;

      while(rbytes =  read(infile, &a, sizeof(a))> 0){

          count = count+1;
    }

    count--;


    char str[2];
    sprintf(str, "%d", count); 

    char spac =' ';
    write(infile, &spac, sizeof(spac));
    write(infile, str, sizeof(str));
    close(infile);



sleep(5);
    printf("Process 2 Finished Count: %d", count);

    sem_post(sem2);
   sem_close(sem);

    return 0;

}
