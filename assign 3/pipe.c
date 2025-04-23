#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
int main(int argc, char *argv[]) 
{ 
int pipefd[2]; 
pid_t cpid; 
if (argc != 3)  
{ 
fprintf(stderr, "Usage: %s <file> <pattern>\n", argv[0]); 
exit(EXIT_FAILURE); 
} 
if (pipe(pipefd) == -1)  
{ 
perror("pipe"); 
exit(EXIT_FAILURE); 
} 
cpid = fork(); 
if (cpid == -1)  
{ 
perror("fork"); 
exit(EXIT_FAILURE); 
} 
if (cpid == 0)  
{   
// Child process (grep <pattern>) 
close(pipefd[1]);  // Close unused write end 
// Redirect stdin to read from pipe 
dup2(pipefd[0], STDIN_FILENO); 
close(pipefd[0]);  // Close after redirection 
// Execute grep with user-provided pattern 
execlp("grep", "grep", argv[2], NULL); 
perror("execlp"); 
_exit(EXIT_FAILURE); 
}  
else  
{          
// Parent process (cat <file>) 
close(pipefd[0]);  // Close unused read end 
// Redirect stdout to write to pipe 
dup2(pipefd[1], STDOUT_FILENO); 
close(pipefd[1]);  // Close after redirection 
// Execute cat <file> 
execlp("cat", "cat", argv[1], NULL); 
perror("execlp"); 
exit(EXIT_FAILURE); 
} 
}