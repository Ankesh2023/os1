#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
  if (argc <3) {
   fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
    	return EXIT_FAILURE;
	}

 const char *source= argv[1];
 const char *dest = argv[2];
    
FILE *sourceFile = fopen(source, "r");

FILE *destFile = fopen(dest, "w");
 
 if (sourceFile == NULL || destFile == NULL) {
 perror("Error file");
 if(sourceFile) fclose(sourceFile);
 if(destFile) fclose(destFile);
  exit(EXIT_FAILURE);
}

    
else{
char buffer[1024];
 while (fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
 	fputs(buffer, destFile);
  }
 
printf("File copied using fgets and fputs.\n");
}
fclose(sourceFile);
fclose(destFile);

return 0;
}





