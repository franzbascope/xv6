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
    int pid;
    int parentpid = getpid();

    for (int i = 0; i < 4; i++)
    {
        pid = fork();

        if (pid < 0) {
            printf(1, "Fork failed\n");
            exit();
        } else if (pid == 0) {
            // Child process
            pid = getpid();
            printf(1, "Child process %d (parent %d)\n", pid, parentpid);
            
            sleep(1000);

            exit();
        }
    }
    for (int i = 0; i < 4; i++) {
        wait(); // Wait for each child process to finish
    }
    
    int ticks = ticks_running(parentpid);
    printf(1,"Process %d has been running for %d ticks.\n", parentpid, ticks);
    exit();
 }