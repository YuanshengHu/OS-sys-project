#include<sched.h>
// this program is used to change the apk to SCHED_FIFo
int main(int argc,char *argv[]){
	struct sched_param parm;				//this struct is used for set the priority
	struct sched_param parm2;
	if(sched_getparam(1365,&parm2)!=-1){			//get the pid use ptree this one is need to be changed when test again
		printf("get the prio");				//this step is to get the priority of origin 
	}
	parm.sched_priority = 10;				//set the priority to 10		
	if(sched_setscheduler(1365,SCHED_FIFO,&parm)!=-1){
		printf("set ok");				//if success we can see "set ok"
	}
	else{
	printf("fail");
	}
	return 0;
}
