#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
	pid_t child_p;

	child_p = fork();

	if (child_p == 0) {
	printf("Child process%d\n", getpid());
	printf("Parent Process: %d\n", getppid());
    
	}
   if (child_p > 0) {
   	wait(NULL);
	printf("Parent process%d\n", getpid());
	printf("Parent's Parent Process: %d\n", getppid());
 
	}
 if(child_p<0){
    	printf("Fork failed");
    	exit(1);
	}

	return 0;
}
