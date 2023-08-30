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

int main(){
    struct msgform msg;
    int msgqid,pid,*pint;
    msgqid=msgget(MSGKEY,0777);
    pid=getpid();
    /*建立消息队列*/
    pint=(int *)msg.mtext;
    *pint=pid;
    msg.mtype=1;
    msgsnd(msgqid,&msg,sizeof(int),0); /*定义消息类型*/
    msgrcv(msgqid,&msg,256,pid,0); /*接受从服务者发来的消息*/
    /*发送消息*/
    printf("[Client] : receive from pid %d\n",* pint);
    return 0;
}
