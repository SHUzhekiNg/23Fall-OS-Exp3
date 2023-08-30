#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MSGKEY 75

struct msgform
{
    /* data */
    long mtype;
    char mtext[256];
}msg;

int msgqid;
void cleanup(void){
    msgctl(msgqid, IPC_RMID, 0);
    exit(0);
}

int main(){
    int i, pid, *pint;
    cleanup();
    for (i=0; i<20; i++)
        signal(i, cleanup);
    msgqid = msgget(MSGKEY, 0777|IPC_CREAT);
    for (;;){
        msgrcv(msgqid, &msg, 256, 1, 0);
        pint = (int *)msg.mtext;
        pid = *pint;
        printf("[SERVER]: receive from pid %d\n", pid);
        msg.mtype = pid;
        *pint = getpid();
        msgsnd(msgqid, &msg, sizeof(int), 0);
    }
    return 0;
}

/*
阅读报告：投资、理财方面的书 文体 格式 不限 2000 第六周周三 提交在xxt
调研报告：小组 自由组合 问卷要>100 第九周交
*/
