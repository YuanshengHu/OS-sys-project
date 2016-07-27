#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
	pid_t Parent;
	Parent = fork();                                                    //fork the process of the parent
	if(Parent==0){
		pid_t Child;
		Child = fork();                                             //fork the process of the child
		if(Child==0){
			while(1);
		}
		else{                                                      //the parent process will begin the testptree
			sleep(1);
			printf("5130309577Child%d\n",Child);
			execl("/data/project1/testARM","testARM",NULL);
		}
	}
	else {
		printf("5130309577Parent:%d\n",Parent);
		while(1);
	}
	return 0;
}
