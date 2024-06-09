#include <stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
int var=4;
sem_t semaphore_NS;
sem_t semaphore_EW;
sem_t semaphore_ped;

void* traffic_light_NorthSouth()
{
    do
    {
        sem_wait(&semaphore_NS);
        //sem_wait(&semaphore_ped);
        usleep(10000);
        printf("  NS  ");
        var--;
        sem_post(&semaphore_EW);
        //sem_post(&semaphore_ped);
    }while(var!=0);
    
}
void* traffic_light_EastWest()
{
    do
    {
        sem_wait(&semaphore_EW);
        //sem_wait(&semaphore_ped);
        usleep(10000);
        printf("  EW  ");
        var--;
        sem_post(&semaphore_NS);
        //sem_post(&semaphore_ped);
    }while(var!=0);
}
//void* pedestrian_crossing()
//{
  //  while(1)
//    {
        
 //   }
//}
int main()
{
pthread_t thread1;
pthread_t thread2;
sem_init(&semaphore_NS, 0, 1);
sem_init(&semaphore_EW, 0, 0);
//sem_init(&semaphore_ped, 0, 0);

pthread_create(thread1,NULL,traffic_light_NorthSouth,NULL);
pthread_create(thread1,NULL,traffic_light_EastWest,NULL);
pthread_join(threads1, NULL);
pthread_join(threads2, NULL);


sem_destroy(&semaphore);

return 0;
}
