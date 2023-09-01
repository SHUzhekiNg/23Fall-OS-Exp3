#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define DEF_SYSTEMV_SEM 1

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int init_sem(int sem_id,int init_value) {
    union semun sem_union;
    sem_union.val=init_value;
    if (semctl(sem_id,0,SETVAL,sem_union)==-1) {
        perror("Error Sem init");
        exit(1);
    }
    return 0;
}

int destory_sem(int sem_id){
    union semun sem_union;
    if (semctl(sem_id,0,IPC_RMID,sem_union)==-1){
        perror("Error Sem delete");
        exit(1);
    }
    return 0;
}

int sem_wait(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num=0;//信号量编号
    sem_buf.sem_op=-1;//P操作
    sem_buf.sem_flg=SEM_UNDO;//系统退出前未释放信号量，系统自动释放
    if (semop(sem_id,&sem_buf,1)==-1) {
        perror("Error sem_wait");
        exit(1);
    }
    return 0;
}
int sem_signal(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num=0;
    sem_buf.sem_op=1;//V操作
    sem_buf.sem_flg=SEM_UNDO;
    if (semop(sem_id,&sem_buf,1)==-1) {
        perror("Error sem_signal");
        exit(1);
    }
    return 0;
}

int main() {
    pid_t pid;

#if DEF_SYSTEMV_SEM
    key_t sem_key=ftok(".","AAAA");
	int sem_id=semget(sem_key,1,0666|IPC_CREAT);

    init_sem(sem_id,1);
#endif

    if ((pid=fork())<0) {
        perror("fork error!\n");
        exit(1);
    } else if (pid==0) {

#if DEF_SYSTEMV_SEM
        sem_wait(sem_id);
#endif

        printf("Child before sleep...\n");
        sleep(2);
        printf("Child after sleep...\n");

#if DEF_SYSTEMV_SEM
        sem_signal(sem_id);
#endif

        exit(0);
    } else {

#if DEF_SYSTEMV_SEM
        sem_wait(sem_id);
#endif

        printf("Parent before sleep...\n");
        sleep(2);
        printf("Parent after sleep...\n");

#if DEF_SYSTEMV_SEM
        sem_signal(sem_id);
        waitpid(pid,0,0);
        destory_sem(sem_id);
#endif

        exit(0);
    }

}