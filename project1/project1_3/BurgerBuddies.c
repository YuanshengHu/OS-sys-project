#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<malloc.h>
#include<signal.h>
#include<fcntl.h> 
#include<sys/ipc.h>   
#include<sys/msg.h>
#include <limits.h>
static int c,s,b,r;
static int ran;
static sem_t c_sem;                                               //define of the semophine
static sem_t b_sem;
static sem_t s_sem;
static sem_t * grand;                                            //semophone array for the casher
static sem_t prin;
struct timeval ts;                                               //timer to generate random number
void icooker(void *arg)                                          //the thread of cooker
{
	int i = *(int*)arg;
	while(1)
	{
		sem_wait(&c_sem);
		sem_wait(&prin);
		printf("Cooker[%d]make a burger.\n",i);          //there is a c_sem for the frank of the buffer
		sem_post(&prin);
		sem_post(&s_sem);                                //s_sem is the not-frank element of the buffer
	}
}
void iserver(void *arg)                                         //the thread of casher
{	
	int i = *(int*)arg;
	while(1)
	{	
		sem_wait(&grand[i-1]);
		sem_wait(&prin);printf("Casher[%d]accepts an order\n",i);sem_post(&prin);	//each printf should be protected
		sem_wait(&s_sem);
		sem_wait(&prin);printf("Casher[%d]take a burger to customor.\n",i);sem_post(&prin);
		sem_post(&c_sem);
	}
}
void ibuyer(void *arg)                                         //the thread of customer
{	
	int i = *(int*)arg;
	gettimeofday(&ts,NULL);
	srand((unsigned int)ts.tv_usec);
	ran = rand()%s;
	sem_wait(&prin);printf("Customer[%d]come.\n",i);sem_post(&prin);
	sem_post(&grand[ran]);
	return;
}
int main(int argc, char *argv[])
{
        sscanf(argv[1],"%d",&c);                                                   //copy the argement
	sscanf(argv[2],"%d",&s);
	sscanf(argv[3],"%d",&b);
	sscanf(argv[4],"%d",&r);
	printf("Cooks[%d],Cashiers[%d],Customers[%d]\n",c,s,b);	
	printf("Begin run.\n");
	sem_init(&prin,0,1);
	sem_init(&c_sem,0,r);
	sem_init(&s_sem,0,0);
 	grand = (sem_t *)malloc(s*sizeof(sem_t));                                 //new the array grand
	int i = 0;
	for(i=0;i<s;i++)	                                                  //generate all the process
	{
		sem_init(&grand[i],0,0);
	}
	for(i=0;i<c;i++)
	{
		pthread_t aa;
		int bb1 = i+1; 
		pthread_create(&aa,NULL,(void*)icooker,(void*)&bb1);
		usleep(20000);
			
	}
	for(i=0;i<s;i++)
	{
		pthread_t aa;
		int bb2 = i+1; 
		pthread_create(&aa,NULL,(void *)iserver,(void*)&bb2);
		usleep(20000);	
	}
	for(i=0;i<b;i++)
	{
		pthread_t aa;
		int bb3 = i+1; 
		pthread_create(&aa,NULL,(void *)ibuyer,(void*)&bb3);	
		usleep(20000);
	}
	while(1);
	return 0;
}
