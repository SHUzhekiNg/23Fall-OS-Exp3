#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i, j;
    printf("My pid is %d, my father's pid is %d\n",getpid(),getppid());
    for(i = 0; i < 3; i++)
        if(fork() == 0)
            printf("%d pid=%d ppid=%d\n", i,getpid(),getppid());
        else
        {
            j = wait(0);
            printf("%d:The chile %d is finished.\n" ,getpid(),j);
        }
    return 0;
}