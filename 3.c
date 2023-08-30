#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int child_pid1,child_pid2,child_pid3;
    int pid,status;
    setbuf(stdout,NULL);

    child_pid1=fork();
    if(child_pid1==0)
    {
        execlp("echo","echo","child process 1",(char *)0); /*子进程1 启动其它程序*/
        perror("exec1 error.\n ");
        exit(1);
    }

    child_pid2=fork();
    if(child_pid2==0)
    {
        execlp("date","date",(char *)0);
        perror("exec2 error.\n ");
        exit(2);
    }

    child_pid3=fork();
    if(child_pid3==0)
    {
        execlp("ls","ls",(char *)0);
        perror("exec3 error.\n ");
        exit(3);
    }
    printf("Parent process is waiting for chile process return!");

    while((pid=wait(&status))!=-1)
    {
        if(child_pid1==pid)
            printf("child process 1 terminated with status %d\n",(status>>8));
        else
        {
            /*若子进程2 结束*/
            if(child_pid2==pid)
                printf("child process 2 terminated with status %d\n",(status>>8));
            else
            {
                /*若子进程3 结束*/
                if(child_pid3==pid)
                    printf("child process 3 terminated with status %d\n" ,(status>>8));
            }
        }
    }
    printf("All child processes terminated.");
    printf("Parent process terminated.");
    exit(0);
    return 0;
}