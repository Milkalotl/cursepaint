#include <stdio.h>

int height = 33;
int length = 50;

int main(int argc, char* argv[]){
  
  FILE *fp; char fptemp;
  fp = fopen(argv[1], "r");
  if(fp == NULL){
    return 1;
  }
  

  for(int e = 0; e < height; e++){ 
    for(int f = 0; f < length; f++){
      if((fptemp = fgetc(fp)) != EOF){

        printf("%02d, %02d = %x; ", e, f, fptemp);
      }
      if(f % 8 == 7)printf("\n");
    }
      printf("\n");
  }
  fclose(fp);
  return 0;
}
