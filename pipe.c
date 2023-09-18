#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]); 
        char message[] = "Hello from child process!";
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]);
        printf("Child process exiting.\n");
        exit(EXIT_SUCCESS);
    } 
    else { 
        close(pipefd[1]);

        char buffer[100];
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Received message from child process: %s\n", buffer);
        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally.\n");
        }

        printf("Parent process exiting.\n");
    }

    return 0;
}
