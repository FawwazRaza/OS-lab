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



    sem = sem_open("/my_semaphore2", O_CREAT, 0644, 0);
    sem2 = sem_open("/my_semaphore3", O_CREAT, 0644, 0);

sem_wait(sem);

    printf("Process 1 Running\n");

      int infile = open("file1.txt", O_RDWR);
      char a;
      int rbytes;
      int sum;

      while(rbytes =  read(infile, &a, sizeof(a))> 0){

          sum = sum + atoi(&a);
    }




    char str[2];
    sprintf(str, "%d", sum); 

    char spac =' ';
    write(infile, &spac, sizeof(spac));

    write(infile, str, sizeof(str));
    close(infile);



sleep(5);
    printf("Process 1 Finished sum: %d", sum);

    sem_post(sem);
   sem_close(sem);

    return 0;

}
