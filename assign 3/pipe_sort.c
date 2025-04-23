#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // Child process: sort data.txt and write to pipe
        close(fd[0]); // Close unused read end
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd[1]);

        execlp("sort", "sort", "data.txt", (char *)NULL);
        perror("execlp sort failed");
        exit(1);
    }

    else {
        // Parent process: read from pipe and run uniq
        close(fd[1]); // Close unused write end
        dup2(fd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(fd[0]);

        execlp("uniq", "uniq", (char *)NULL);
        perror("execlp uniq failed");
        exit(1);
    }

    return 0;
}
