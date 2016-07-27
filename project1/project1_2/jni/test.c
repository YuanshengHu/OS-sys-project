#include<stdio.h>
#include<mystruct.h>                                               //.h file define the struct
int main(){
	printf("This is a test:\n\n");         
	struct prinfo input[50];
	int b = 50;
	int * nr = &b;
	int j = syscall(356,input,nr);                             //syscall
	printf("the number of the processes is %d\n",j);
	int i;
	for(i = 0; i<*nr; i++){                                    //print
		printf("%s,%d,%ld,%d,%d,%d,%d\n",(&input[i])->comm,(&input[i])->pid,input[i].state,input[i].parent_pid,input[i].first_child_pid,input[i].next_sibling_pid,input[i].uid);
	}
	printf("Test End!:\n\n");
	return 0;
}
