#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int traffic_light_NS1 = 0; 
int traffic_light_EW1 = 0; 
int pedestrian_signal_NS = 0; 
int pedestrian_signal_EW = 0; 
sem_t semaphore_NS, semaphore_EW, semaphore_ped;

void *traffic_light_NS(void *arg);
void *traffic_light_EW(void *arg);
void *pedestrian_crossing(void *arg);

void *traffic_light_NS(void *arg) 
{
    while (1)
    {
        sem_wait(&semaphore_NS);
        
        traffic_light_NS1 = !traffic_light_NS1;
        if (traffic_light_NS1) 
        {
            printf("North-South moving\n");
        }
        else
        {
            printf("North-South stop\n");
        }
        sem_post(&semaphore_NS);
        sleep(5); 
        }
    return NULL;
}

void *traffic_light_EW(void *arg) 
{
    while (1)
    {
        sem_wait(&semaphore_EW);
        traffic_light_EW1 = !traffic_light_EW1;
        if (traffic_light_EW) 
        {
            printf("East-West moving\n");
        }
        else
        {
            printf("East-West stop\n");
        }
        sem_post(&semaphore_EW);
        sleep(5); 
    }
    return NULL;
}

void *pedestrian_crossing(void *arg)
{
    while (1) 
    {
        sem_wait(&semaphore_ped);
        pedestrian_signal_NS = !pedestrian_signal_NS;
        pedestrian_signal_EW = !pedestrian_signal_EW;
        if (pedestrian_signal_NS) 
        {
            printf("Pedestrian  North-South \n");
        } 
        else
        {
            printf("Pedestrian  North-South Don't Walk\n");
        }
        if (pedestrian_signal_EW) 
        {
            printf("Pedestrian  East-West Walk\n");
        } 
        else
        {
            printf("Pedestrian  East-West Don't Walk\n");
        }
        sem_post(&semaphore_ped);
        sleep(2); 
    }
    return NULL;
}
int main() 
{
    pthread_t thread_NS, thread_EW, thread_ped;
    
    
    sem_init(&semaphore_NS, 0, 1);
    sem_init(&semaphore_EW, 0, 1);
    sem_init(&semaphore_ped, 0, 1);
    
    pthread_create(&thread_NS, NULL, traffic_light_NS, NULL);
    pthread_create(&thread_EW, NULL, traffic_light_EW, NULL);
    pthread_create(&thread_ped, NULL, pedestrian_crossing, NULL);
    
    pthread_join(thread_NS, NULL);
    pthread_join(thread_EW, NULL);
    pthread_join(thread_ped, NULL);
    
    sem_destroy(&semaphore_NS);
    sem_destroy(&semaphore_EW);
    sem_destroy(&semaphore_ped);
    
    return 0;
}


