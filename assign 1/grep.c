#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
if (argc < 3) {
 fprintf(stderr, "Usage: %s <source_file> <pattern>\n", argv[0]);
 return EXIT_FAILURE;
 }

 const char *src = argv[1];
const char *pattern = argv[2];
   
FILE *sourceFile = fopen(src, "r");

char buffer[1024];
 
 if (sourceFile == NULL) {
 perror("Error file");
  return EXIT_FAILURE;
}
else{
int count=0;
   while (fscanf(sourceFile, "%1023[^\n]\n", buffer) == 1) {
   if (strstr(buffer, pattern) != NULL) {
   count++;
  printf("%s\n",buffer);
	}
 }
 printf("Word occured in %d line\n", count);
}
 fclose(sourceFile);
return EXIT_SUCCESS;

}


