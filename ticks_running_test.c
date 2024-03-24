#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
 
int 
main(void) {
    int pid = getpid();
    
    int ticks = ticks_running(pid);
    printf(1,"Process %d has been running for %d ticks.\n", pid, ticks);

    for (int i = 0; i < 1000; i++)
    {
        printf(1,"Waiting...\n");
    }
    

    ticks = ticks_running(pid);
    printf(1,"Process %d has been running for %d ticks.\n", pid, ticks);
    exit();
 }