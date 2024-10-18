#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


#include "fileio.h"
#include "cursepaint.h"





char savename[64] = "";
char curdir[] = "";



int savefunc(void){
  if (strcmp(savename, "")!=0){
  mvprintw(0,0,"Do you want to give a new filename? (Y)es, (N)o: ");
  temp = getch();
  if(temp != 'y'){return truesave();}
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
  
  strcat(savename, ".txt");
  strcat(curdir, savename);
  

  clear();
  refresh();
  return truesave();
}


int truesave(){
  FILE *fp;
  fp = fopen(curdir, "w+");
  for(int e = 0; e < height; e++){ 
    for(int f = 0; f < length; f++){
      fputc(board[e][f],fp);
    }
    fputc('\n', fp);
  }
  fclose(fp);
return 0;
}
