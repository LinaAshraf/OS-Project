#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"
extern int completed_processes;
extern int total_waiting_time;
uint64
sys_getwait(void)
{
  return myproc()->waiting_time;
}

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}
uint64
sys_get_avg_waiting_time(void)
{
  return (completed_processes > 0) ? total_waiting_time / completed_processes : 0;
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// Helper function to safely copy strings

uint64 sys_getptable(void) {
  uint64 addr;
  int nproc;


  // Use temp variables to capture errors
  argint(0, &nproc);
  argaddr(1, &addr);

  // Manually verify arguments
  struct proc *p = myproc();
  if(addr >= p->sz || addr+sizeof(struct pstat) > p->sz)
  return -1;

  return getptable(nproc, addr);
}
uint64
sys_setpriority(void) {
  int prio;
  argint(0, &prio);  // note: no checking return value, argint returns void

  if(prio < 0) prio = 0;
  if(prio > 9) prio = 9;

  myproc()->priority = (uint64)prio;
  return 0;
}

uint64
sys_getppid(void)
{
    struct proc *p = myproc();

    if(p->parent)  // Check if parent exists
        return p->parent->pid;
    return 1;  // Return 1 (init's PID) if no parent
}
uint64
sys_getpriority(void) {
  return myproc()->priority;
}
