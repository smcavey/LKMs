/*
* File: hw2.c
* Purpose: To demonstrate a kernel module that lists processes 
*/
#include <linux/module.h> /* for all kernel modules */
#include <linux/kernel.h> /* for KERN_INFO */
#include <linux/init_task.h>
#include <linux/list.h>
#include <linux/sched.h>

int init_module( void ) /* module entry point */
{
	int count = 0;
	static LIST_HEAD(tasks);
	struct task_struct *task;
	task = &init_task;

	printk( KERN_INFO "Hello, Spencer McAvey!\n" );
	printk( KERN_INFO "init process: \n");
	pr_info("Task: %-20s pid: %d \t Priority: %d \t State: %ld \t CPU core number: %d \t Parent Task: %-20s \t ppid: %d\n",
		task->comm, task->pid, task->rt_priority, task->state, task->cpu, task->group_leader->comm, task_ppid_nr(task));
/* getting task name, task pid, task priority, task state, which core task is running on, task's parent name, task's parent pid */
//	for_each_process(task) alternative way
	list_for_each_entry(task, &current->tasks, tasks)
	{	
		count = count + 1;
		pr_info("Task: %-20s pid: %d \t Priority: %d \t State: %ld \t CPU core number: %d \t Parent Task: %-20s \t ppid: %d\n",
			task->comm, task->pid, task->rt_priority, task->state, task->cpu, task->group_leader->comm, task_ppid_nr(task));
	}
	printk( KERN_INFO "Current Process: \n" );
	pr_info("Task: %-20s pid: %d \t Priority: %d \t State: %ld \t CPU core number: %d \t Parent Task: %-20s \t ppid: %d\n",
		current->comm, current->pid, current->rt_priority, current->state, current->cpu, current->group_leader->comm, task_ppid_nr(current));
	printk( KERN_INFO "Total Process Count: %d\n", count);
	return 0;
}

void cleanup_module( void ) /* module exit point */
{
	printk( KERN_INFO "Goodbye, Spencer McAvey!\n" );
	return;
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My first cool kernel module");
MODULE_AUTHOR("Spencer McAvey");
