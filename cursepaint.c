#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cursepaint.h"

char savename[64] = "";

int height = 33;
int length = 48;
char board[33][48];
int posx = 12;
int posy = 12;

int spacing = 2;


char temp;
char print = 'b';
int panel2temp = 2;

float version = 0.05;



int brushnum = 23;
char brushes[] = { 
  'b', 'E', '+',  '#' ,'/', '\\', '(', ')', '-', '|', '_', '.', '*', 'o', '"', '$', '@','V', 'A', '%', 'w','W','H', 'y'
};
int brushc = 0;
int hold = 2;

WINDOW *win; 
WINDOW *panel;
WINDOW *panelb;

int main(){
  
  initscr();
  noecho();

  for(int e = 0; e<height; e++){
    for(int f = 0; f<length; f++){
      board[e][f] = ' ';
    }
  }


  

  mvprintw(7, 85, "CURSE PAINT V%f", version);


  
  start_color();

  init_pair(2, COLOR_CYAN, COLOR_BLUE);
  
  win = newwin(35,50,9,80);
  panel = newwin(5,10,9,65);
  panelb = newwin(27, 10, 17, 65);


  do{
  ptspanel();
  ptswin();
  temp = inputmove(); 
  }while(1);
  return 0;
}

void ptswin(void){
  wborder(win, '[',']','-','-','*','*','L','/');
  
  

  if(print != 'b' && print != 'E'){ 
    attron(COLOR_PAIR(2));
    mvwaddch(win,posy,posx,print); 
    attroff(COLOR_PAIR(2)); 
    board[posy-1][posx-1] = print;  
  }else if(print == 'E'){
      
    mvwaddch(win,posy,posx,' '); 
    board[posy-1][posx-1] = ' ';  

}else{
    wmove(win, posy, posx);
}
  wrefresh(win);

}

void ptspanel(void){
  wborder(panel, '|','|','-','-','+','+','+','+');
  wborder(panelb, '|','|','-','-','+','+','+','+'); 

  mvwprintw(panel, 1,2, "%c || %c", print, brushes[hold]);
  mvwprintw(panel, 3,2, "spa: %d", spacing);
  
  for(int e = 0; e <= brushnum; e++){
    if(e%2 == 0) {mvwaddch(panelb, e+2, 2, brushes[e]);}
    else{mvwaddch(panelb, e+1, 7, brushes[e]);}
  }
  mvwaddch(panelb, panel2temp, 4, ' ');mvwaddch(panelb, panel2temp-1, 5, ' ');

  if(brushc %2 == 0){mvwaddch(panelb, brushc+2, 4, '<');}
  else{mvwaddch(panelb, brushc+1, 5, '>');}
  panel2temp = brushc+2;
  
  wrefresh(panelb);
  wrefresh(panel);
}




char inputmove(void){
  int dir = getch();
  switch(dir){
    case 'w': posy--; break;
    case 's': posy++; break;
    case 'd': posx+=spacing; break;
    case 'a': posx-=spacing; break;
    case ' ':
    if(print != 'b' && print != 'E'){hold = brushc; brushc = 0;}else{brushc = hold;} break;
    case 'e':
    (print != 'E')? (brushc = 1):(brushc = 0); break; 
   

    case 'j': brushc --; break;
    case 'k': brushc ++; break;
    case 'u': brushc -= 2; break;
    case 'i': brushc += 2; break;
    
    case '.': spacing ++; if(spacing>8){spacing = 8;} break;
    case ',': spacing --; if(spacing<1){spacing = 1;} break;

              
    case 't': inputtext(); break;

    case '+': savefunc(); break;
    case 'q': quitfunc(); break;
  }
  if(dir >= '0' && dir <= '9'){
    dir -= '0';
    if(dir == 0){dir = 10;} 
    dir =  (dir - 1)*2;
    brushc = dir;


  }


  if(brushc > brushnum){brushc = 0;} 
  if(brushc < 0){brushc = brushnum;} 
  print = brushes[brushc];
  
  return dir;
}

void inputtext(void){
  mvprintw(6,80, "TEXT MODE");
 int storage = 0;

  while(1){
    storage = getch();
    if (storage == '\n'){return;}
    if (storage == KEY_LEFT){
      posx-=spacing;
      mvwaddch(win, posy, posx, ' ');
      board[posy-1][posx-1] = ' ';  
   
    }else{
      mvwaddch(win, posy, posx, storage);
      board[posy-1][posx-1] = storage;  
      posx+=spacing;
    }  
    wrefresh(win);
  }
  clear();
  refresh();

}


void quitfunc(){
  clear();
  printw("Are you sure? (Y)es, (N)o.");
  temp = getch();
  if(temp != 'y'){/*printw(" || %c ||", temp);*/ clear(); refresh(); return;}
  clear();
  refresh();  
  
  for(int e = 0; e<height; e++){
    for(int f = 0; f<length; f++){
      mvwaddch(stdscr,e+1, f, board[e][f]);
      if(f == length-1){addch('!');}
    }
  }
mvprintw(0,0,"would you like to save this image ? (Y)es, (N)o, (R)eturn");
  temp = getch();
if(temp != 'y' && temp != 'n'){clear(); refresh(); return;}
if(temp == 'y'){savefunc(); }  
  delwin(panelb);
  delwin(panel);
  delwin(win);

  getch();
 endwin();
  exit(0);
}


int savefunc(void){
  

  echo();
  

  if (strcmp(savename, "")!=0){
  mvprintw(0,0,"Do you want to give a new filename? (Y)es, (N)o: ");
  if(getch() != 'y'){return truesave();}
  }
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
  clear();
  refresh();
  return truesave();
}
int truesave(){
  FILE *fp;
  fp = fopen(savename, "w+");
  for(int e = 0; e < height; e++){ 
    for(int f = 0; f < length; f++){
      fputc(board[e][f],fp);
    }
    fputc('\n', fp);
  }
  fclose(fp);
return 0;
}
