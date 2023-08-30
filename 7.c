#include<stdio.h>
#include<stdlib.h>

int func(void){
    int m;
    m = getpid();
    printf("Process %d, signal 18 processing function. \n", m);
}

int main(){
    int i, j, k;
    func();
    signal(18, func());

    if(i=fork()){
        j=kill(i,18);
        printf("[PARENT]: signal 18 has been sent to child %d, returned %d. \n",i,j);
        k=wait();
        printf("After wait %d, Parent %d: finished. \n",k,getpid());
    }
    else{
        sleep(3);
        printf("[CHILD] %d: A signal from my parent is received. \n", getpid());
    }
    return 0;
}