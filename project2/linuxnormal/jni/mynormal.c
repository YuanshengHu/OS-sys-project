#include<sched.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
//this a linux program which use default scheduler
int main(int argc,char *argv[]){                                //just do nothing		
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
	printf("\nnormaltime = %llu\n",second-first);			//show the between time
	return 0;
}
