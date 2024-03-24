#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

void run_stressfs()
{
    printf(1,"stressfs running\n");
    int pid;
    int ticks;

    pid = fork();
    if (pid < 0)
    {
        printf(1, "Fork failed\n");
        exit();
    } else if (pid == 0)
    {
        char *argv[] = {"stressfs", 0};
        exec("stressfs",argv);
        exit();
    }
    else
    {   
        wait();
        pid = getpid();
        ticks = ticks_running(pid);
        printf(1,"stressfs has been running for %d ticks.\n", ticks);
    }
}

void run_find()
{
    printf(1,"find running\n");
    int pid;
    int ticks;

    pid = fork();
    if (pid < 0)
    {
        printf(1, "Fork failed\n");
        exit();
    } else if (pid == 0) {
        char *argv[] = {"find", ".", "-name", "README", 0};
        exec("find",argv);
        exit();
    }
    else
    {   
        wait();
        pid = getpid();
        ticks = ticks_running(pid);
        printf(1,"find has been running for %d ticks.\n", ticks);
    }
}

void run_cat_uniq()
{
    printf(1,"Cat/Uniq running\n");
    int pid;
    int ticks;
    
    pid = fork();
    if (pid < 0)
    {
        printf(1, "Fork failed\n");
        exit();
    } else if (pid == 0) {
        printf(1,"Cat running\n");
        char *argv[] = {"cat","test_uniq.txt", 0};
        exec("cat",argv);
        exit();
    }
    else
    {   
        pid = fork();
        if (pid < 0)
        {
            printf(1, "Fork failed\n");
            exit();
        }
        else if (pid == 0)
        {
            printf(1,"Uniq running\n");
            char *argv[] = {"uniq", "test_uniq.txt", 0};
            exec("uniq", argv);
            exit();
        }
        else
        {
            //wait();
            //wait();

            pid = getpid();
            ticks = ticks_running(pid);
            printf(1,"Cat/Uniq has been running for %d ticks.\n", ticks);
            exit();
        }
    }
}

int main(void) {
    run_stressfs();
    run_find();
    run_cat_uniq();

    exit();
}