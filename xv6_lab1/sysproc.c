#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_count(void)
{
	return proc->count;
}
int
sys_fork(void)
{
  return fork();
}

//edited to take stat argument
int
sys_exit(void)
{
  int status;
  //status gaken from 
  //argint
  if(argint(0, &status) < 0)
    return -1;
  else
    exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status;
  if(argptr(0,(char**) &status, sizeof(status)) < 0)
    return -1;
  return wait(status);
}

int
sys_waitpid(void)
{
  int *status;
  int options;
  int pid;

  if (argint(0, &pid) <0)
    return -1;
  if (argptr(1, (char **) &status, sizeof(status)) <0)
    return -1;
  if(argint(2, &options) < 0)
    return -1;

  return waitpid(pid,status,options);
}

int
sys_change_priority(void)
{
  int priority;
  if (argint(0, &priority) <0 )
    return -1;
  return change_priority(priority);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
