#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/unistd.h>
#include<linux/uaccess.h>
static int tab = 0;
MODULE_LICENSE("Dual BSD/GPL");
#define __NR_hellocall 356
struct prinfo{                                                          //the struct prinfo define
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_pid;
	long state;
	long uid;
	char comm[64];
};
static int (*oldcall)(void);
static int sys_hellocall(struct prinfo *buf, int *nr)                  //the syscall define
{
	int a = 0;                                                      //
	int *count = &a;                                                //the counter
	struct task_struct *task;                                       //
	task = current;							//pointer of the current process
	while(task->pid!=0)task = task->parent;				//find all the process's father
	char* m = "";							//
	struct list_head *list;						//
	read_lock(&tasklist_lock);				        //lock the list of task_struck
FUCK:        
	printk("\n%d\n",*count);
	printk("\n%d\n",*nr);	
 	if(*count<*nr)							//this part is used for the copy
	{
		if(task->pid!=0 && task->real_parent!=NULL)
		{
			printk("cc");					//
			buf[*count].parent_pid = task->real_parent->pid;printk("k");
		}
		else buf[*count].parent_pid = 0;			//
		buf[*count].pid = task->pid;
		if(!list_empty(&(task->children)))
		{
			struct list_head *list = (&(task->children))->next;	
			buf[*count].first_child_pid = list_entry(list,struct task_struct,sibling)->pid;
		}
		else buf[*count].first_child_pid = 0;
		if(task->pid!=0 && (&(task->parent->children))->next->next!=(&(task->parent->children)))
		{
			struct list_head *list = (&(task->sibling))->next;
			buf[*count].next_sibling_pid = list_entry(list,struct task_struct,sibling)->pid;
		}
		else buf[*count].next_sibling_pid = 0;		
		buf[*count].state = task->state;
		buf[*count].uid = task->real_cred->uid;
		{		
 			int i=0;
			for(i=0; i<tab; i++)
			{
				buf[*count].comm[i] = '\t';	
			}
			for(; task->comm[i-tab]!='\0'; i++)
			{
				buf[*count].comm[i] = task->comm[i-tab];
			}
			buf[*count].comm[i-tab] = '\0';
		}
		
	}
	list_for_each(list,&task->children)                                  //search for the first child
	{	
	 	(*count)++;
		tab++;
		task = list_entry(list,struct task_struct,sibling);
                goto FUCK;
	}
NANI:
	if(task->pid==0)goto HE;                                           //if all the search finish goto HE
	if(task==list_entry((&(task->real_parent->children))->prev,struct task_struct,sibling))
	{
		task = task->parent;
		tab--;                                                     //if already be the father's last child back to father 
		goto NANI;
	}
	else 
	{
		++(*count);                                               //else get the next sibling
		task = list_entry((&task->sibling)->next,struct task_struct,sibling);	
		goto FUCK;                                                //use to go back;
	}        
HE:
	read_unlock(&tasklist_lock);
	*nr = ((*count)>=*nr)?*nr:(*count)+1;
	return ++(*count);
}
static int addsyscall_init(void)
{
	long *syscall = (long*)0xc000d8c4;
	oldcall = (int(*)(void))(syscall[__NR_hellocall]);
	syscall[__NR_hellocall] = (unsigned long )sys_hellocall;
	printk(KERN_INFO "module load!\n");
	return 0;
}
static void addsyscall_exit(void)
{
	long *syscall = (long*)0xc000d8c4;
	syscall[__NR_hellocall] = (unsigned long )oldcall;
	printk(KERN_INFO "module exit!\n");
}
module_init(addsyscall_init);
module_exit(addsyscall_exit);
