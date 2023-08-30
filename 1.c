#include<stdio.h>
#include<stdlib.h>
int main(){
    int i;
    if (fork()){
        i = wait();
        printf("It is parent process.\n");
        printf("The child process,ID number %d, is finished.\n",i);
    }
    else{
        printf("It is child process.\n");
        sleep(1);
        exit(0);
    }
    return 0;
}