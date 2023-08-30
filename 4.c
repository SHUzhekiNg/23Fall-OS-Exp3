#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int global_cnt=4;
int main(){
    pid_t pid;
    int vari=5;
    printf("before fork.\n");
    if ((pid=fork())<0)
    {
        /*创建失败处理*/
        printf("fork error.\n");
        exit(0);
    }
    else
        if(pid==0)
        {
            /*子进程执行*/
            global_cnt++;
            vari--;
            printf("Child %d changed the vari and global_cnt.\n",getpid());
        }
        /*父进程执行*/
        else
        printf("Parent %d did not changed the vari and global_cnt.\n",getpid());
        printf("pid=%d, global_cnt=%d, vari=%d\n",getpid(),global_cnt,vari);
        exit(0);

    return 0;
}