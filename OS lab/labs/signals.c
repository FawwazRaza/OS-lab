#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int count = 0; 

void foo(int signum);

void foo(int signum)
{
    printf("total time  %d seconds\n", count);
    exit(1);
}

int main()
{
    int num1, num2;
    
    printf("Please enter  laps: \n");
    scanf("%d", &num1);
    printf("Please enter the lap time \n");
    scanf("%d", &num2);

    pid_t pid = fork();

    if (pid == 0) 
    { 
        
        for (int i = 1; i <= num1; i++) 
        {
            printf("Lap %d completed\n", i);
            //sleep(num2);
            count += num2; 
        }
        exit(0); 
    } 
    else if (pid > 0) 
    { 
        
        signal(SIGSTOP, foo); 
         
    } 
    else
    { 
        
        perror("Fork failed");
        exit(1);
    }

return 0;
}