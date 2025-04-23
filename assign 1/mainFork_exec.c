#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

void copyCommand(const char *source , const char *destination){
  pid_t child_p;

	child_p = fork();

	if (child_p == 0) {
	printf("Executing copy ");
  	execlp("./copy", "./copy",source, destination, NULL);
	printf("Child process%d\n", getpid());
   // printf("Parent Process: %d\n", getppid());
    
	}
   if (child_p > 0) {
   	wait(NULL);
	printf("Parent process%d\n\n", getpid());
   // printf("Parent's Parent Process: %d\n", getppid());
 
	}
 if(child_p<0){
    	printf("Fork failed");
    	exit(1);
	}

}

void grepCommand(const char *source , const char *pattern){
	pid_t child_p;

	child_p = fork();

	if (child_p == 0) {
    
	printf("Executing grep");
 	execlp("./grep", "./grep", source, pattern, NULL);
	printf("Child process%d\n", getpid());
  //  printf("Parent Process: %d\n", getppid());
    
	}
   if (child_p > 0) {
   	wait(NULL);
	printf("Parent process%d\n\n", getpid());
  //  printf("Parent's Parent Process: %d\n", getppid());
 
	}
 if(child_p<0){
    	printf("Fork failed");
    	exit(1);
	}

}

int main(int argc, char *argv[]) {
if(argc<2){
printf("Enter atleast 2 arguments.\n");
 return EXIT_FAILURE;
}

 const char *source= argv[1];
 const char *dest = argv[2];
const char *pattern = argv[3];
   
while(1){
   int c;
   printf("Enter 1 for copy command\nEnter 2 for grep \nEnter 3 for exit:");
   scanf(" %d", &c);   
   switch (c){
   case 1:
   copyCommand(source, dest);
   break;
   case 2:
	grepCommand(source, pattern);
	break;
	case 3:
	return 0;
	default:
 	return 0;
   }
}
	return 0;
}

