#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_
struct prinfo{
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_pid;
	long state;
	long uid;
	char comm[64];
};
#endif/*MYSTRUCT_H_*/
