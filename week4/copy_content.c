#include <stdio.h>
#include <stdlib.h>


typedef struct phoneaddress {
	char name[20];
	char tel[11];
	char email[25];
}


int main(int argc, char**argv) {
  FILE *fptr1;
  FILE *fptr2;
  char *infile = argv[1];
  char *outfile = argv[2];

  if ((fptr1 = fopen(infile, "rb")) == NULL  || (fptr2 = fopen(outfile, "wb")) == NULL) {
    printf("Cannot open files\n");
    return 0;
  }

  int num;
  void *buff;
  int MAX_LEN=100;
  int buff_size = 1;

  buff = malloc(buff_size);
  while(!feof(fptr1)) {
	  num = fread(buff, buff_size, MAX_LEN, fptr1);
	  fwrite(buff, buff_size, num, fptr2);
  }

  fclose(fptr1);
  fclose(fptr2);
  
  return 0;
}
