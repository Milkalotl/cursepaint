#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <dirent.h> 

#include "fileio.h"
#include "cursepaint.h"




const char foldir[] = "./images/"; 
char savename[128] = "NOFILE";
char curdir[128] = "";

void candfdir(void){

  strcpy(curdir, foldir);
  strcat(curdir, savename);
  strcat(curdir, ".txt");

}

int savefunc(void){
  if (strcmp(savename, "NOFILE")!=0){
  mvprintw(0,0,"Do you want to give a new filename? (Y)es, (N)o: ");
  temp = getch();
  if(temp != 'y'){clear(); return truesave();}
  }
  echo();
  do{
  clear(); refresh();
  mvprintw(0,0,"Please state the save name: ");
  refresh();
  getstr(savename);
  mvprintw(2,0, "Is %s.txt your desired filename? (Y)es, (N)o ", savename);
  refresh();
  temp = getch();
  }while(temp != 'y');
  noecho();
  
  candfdir(); 

  clear();
  refresh();
  return truesave();
}


int truesave(){
  FILE *fp;
  fp = fopen(curdir, "w");
  for(int e = 0; e < height; e++){ 
    for(int f = 0; f < length; f++){
      fputc(board[e][f],fp);
    }
    fputc(10, fp);
  }
  fclose(fp);
return 0;
}

int openfunc(char* filename){
  FILE *fp; char fptemp;
  strcpy(savename, filename);
  candfdir();
  
  fp = fopen(curdir, "r");
  if(fp == NULL){
    return 1;
  }
  

  for(int e = 0; e < height; e++){ 
    for(int f = 0; f < length; f++){
      if((fptemp = fgetc(fp)) != EOF){
        if (fptemp == '\n'){break;}
        board[e][f] = fptemp;
      }
    }
  }
  fclose(fp);
  
  strcpy(savename, filename);

  return 0;
}

int showdir(char* givendir){
  DIR *d; int line = 0;
  struct dirent *dir;
  d = opendir(givendir);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      mvprintw(line, 0,"%s", dir->d_name);
      line++;
    }
    closedir(d);
  }
  return line;
}






