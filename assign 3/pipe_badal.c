#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    int filedes = open("file.txt", O_RDONLY);
    if (filedes < 0) {
        perror("filedes can't open for read...");
        exit(1);
    }

    if (pipe(fd) == -1) {
        perror("can't create pipe");
        exit(1);
    }

    dup2(filedes, STDIN_FILENO);
    close(filedes);

    pid = fork();
    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to pipe write end
        close(fd[0]);  // Close unused read end
        close(fd[1]);

        execl("/usr/bin/sort", "sort", (char *)NULL);
        perror("execl sort error");
        exit(1);
    } else if (pid > 0) {
        // Parent process: uniq
        close(fd[1]);  // Close unused write end
        waitpid(pid, NULL, 0);  // Wait for child

        dup2(fd[0], STDIN_FILENO);  // Redirect stdin to pipe read end
        close(fd[0]);

        execl("/usr/bin/uniq", "uniq", (char *)NULL);
        perror("execl uniq error");
        exit(1);
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;
}
