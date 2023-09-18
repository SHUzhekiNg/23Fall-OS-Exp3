#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = getpid();
    pid_t gid = getpgid(pid);
    uid_t uid = getuid();

    printf("PID: %d\n", pid);
    printf("GID: %d\n", gid);
    printf("UID: %d\n", uid);
    sleep(5);

    char choice;
    printf("是否执行ls? (Y/N): ");
    scanf("%c", &choice);

    if (choice == 'Y' || choice == 'y') {
        execl("/bin/ls", "ls", NULL);
    } else {
        printf("操作结束\n");
    }

    return 0;
}
