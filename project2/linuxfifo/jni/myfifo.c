#include<sched.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
//this a linux program which has a long loop and use the fifo scheduler
int main(int argc,char *argv[]){
	struct sched_param parm;				//the struct used to set the priority
	struct sched_param parm2;
	if(sched_getparam(getpid(),&parm2)!=-1){
		printf("get the prio");
	}							//get the origin priority
	parm.sched_priority = 10;				//set the priority to be 10
	if(sched_setscheduler(getpid(),SCHED_FIFO,&parm)!=-1){
		printf("set ok");				
	}							//set the scheduler to be fifo			
	struct timeval tv1;
	struct timeval tv2;					//this struct used to show time
	gettimeofday(&tv1,NULL);				//get the time before loop
	unsigned long long first =tv1.tv_sec*1000000+tv1.tv_usec;	
	int loop = 20000;
	int i=0;
	int a=0;
	int b=0;
	int c=0;						//the loop
	for(;i<loop;i++){
		a++;
		b++;
		c+=a*b;
		printf("a");	
	
	}
	gettimeofday(&tv2,NULL);				//get the time after the loop
	unsigned long long second =tv2.tv_sec*1000000+tv2.tv_usec;
	printf("\nfifotime = %llu\n",second-first);			//show the between time
	return 0;
}
