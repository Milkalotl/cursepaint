#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "fileio.h"
#include "cursepaint.h"
#include "setup.h"





float version = 0.09;



int height = 33;
int width = 49;
char * board;
int posx = 12;
int posy = 12;

int spacing = 2;


char temp;
char print = 'b';
int panel2temp = 2;

int brushnum = 25;
char brushes[] = { 
  'b', 'E', '+',  '#' ,'/', '\\', '(', ')', '<', '>', 'V', 'A', '-', '|', '_', '=','.', '*', 'o',  '$', '@', '%', 'w','W','H', 'y'
};
int brushc = 0;
int hold = 2;

WINDOW *win; 
WINDOW *panelh;
WINDOW *panelb;
WINDOW *panels;
WINDOW *panelt;
WINDOW *panelc;


void clear_canvas(bool is_window_active){ 
  
  for(int e = 0; e<height; e++) 
    for(int f = 0; f<width; f++) {
      *(board + e*height + f) = ' ';
      if(is_window_active == TRUE) mvwaddch(win,posy,posx,' '); 
    }


}

void kill_quit(int condition){
  endwin();
  free(board);
  exit(condition);
}

int main(){
  
  printf("This application will start N-Curses. Please do not kill the process with ctrl-c or ctrl-d unless something has gone seriously wrong. There will be commands associated to q and Q if one wishes to quit safely. If you wish to quit right now, press q. Otherwise, welcome to CURSEPAINT\n: ");
  if(getchar() == 'q')kill_quit(0); 
  initscr();
  noecho();
  
  setup(); //from setup.c
  

  clear_canvas(FALSE); 

  start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(11, COLOR_WHITE, COLOR_WHITE);
    init_pair(12, COLOR_RED, COLOR_RED);
    init_pair(13, COLOR_BLUE, COLOR_BLUE);
    init_pair(14, COLOR_GREEN, COLOR_GREEN);


  win = newwin(height+2,width+2,height/2,width/2); //canvas
  panels = newwin(5, width+30/*10+10+6+4*/, height/2-6, width/2-14); //top header, shows filename and stats
  panelh = newwin(5,10,height/2,width/2-14); // shows basic data - brush panel info
  panelb = newwin(4+brushnum, 10, height/2+5, width/2-14); // brushes
  panelt = newwin(29, 10, height/2, 3*width/2 + 6); // tools
  panelc = newwin(5,10, 3*height/2 -9, 3*width/2 + 6); // custom

  // fix these 
  

  do{
  border_print_once();
  ptspanel();
  ptswin();
  temp = inputmove(); 
  }while(1);

  endwin();
  free(board);

  return 0;
}

void border_print_once(void){
  wattron(win, COLOR_PAIR(6)); 
    wborder(win, '[',']','-','-','*','*','L','/');
    wrefresh(win);
  wattron(panelh, COLOR_PAIR(2));
    wborder(panelh, '|','|','-','-','+','+','+','+');
    wrefresh(panelh);
  wattron(panelb, COLOR_PAIR(3));
    wborder(panelb, '|','|','-','-','+','+','+','+'); 
    wrefresh(panelb);
  wattron(panels, COLOR_PAIR(4)); 
    wborder(panels, '|','|','-','-','+','+','+','+');
    wrefresh(panels);
  wattron(panelc, COLOR_PAIR(6)); 
    wborder(panelc, '|','|','-','-','+','+','+','+');
    wrefresh(panelc);
  wattron(panelt, COLOR_PAIR(7)); 
    wborder(panelt, '|','|','-','-','+','+','+','+'); 
    wrefresh(panelt);
  standend();
}

void ptswin(void){
  
  

  if(print != 'b' && print != 'E'){ 
   // wattron(win, COLOR_PAIR(13));
    mvwaddch(win,posy,posx,print); 
   // wattroff(win, COLOR_PAIR(13)); 
    *(board + height * (posy-1) + posx-1) = print;  
  }else if(print == 'E'){
      
    mvwaddch(win,posy,posx,' '); 
    *(board + height * (posy-1) + posx-1) = ' ';  

}else{
    wmove(win, posy, posx);
}
  wrefresh(win);

}

void ptspanel(void){

  mvwprintw(panels, 2, (width+30)/2-9, "CURSE PAINT V%f", version);
  mvwprintw(panels, 3, (width+30)/2-9, "%s", savename);
  

  mvwprintw(panelh, 1,2, "%c || %c", print, brushes[hold]);
  mvwprintw(panelh, 3,2, "spa: %d", spacing);
  
  for(int e = 0; e <= brushnum; e++){
    if(e%2 == 0) {mvwaddch(panelb, e+2, 2, brushes[e]);}
    else{mvwaddch(panelb, e+1, 7, brushes[e]);}
  }
  mvwaddch(panelb, panel2temp, 4, ' ');mvwaddch(panelb, panel2temp-1, 5, ' ');

  if(brushc %2 == 0){mvwaddch(panelb, brushc+2, 4, '<');}
  else{mvwaddch(panelb, brushc+1, 5, '>');}
  panel2temp = brushc+2;
 
  wrefresh(panels);
  wrefresh(panelb);
  wrefresh(panelh);
  wrefresh(panelt);
  wrefresh(panelc);

}




char inputmove(void){
  int dir = getch();
  switch(dir){
  


    case ' ':
    if(print != 'b'){if(print != 'E'){hold = brushc;} brushc = 0;}else{brushc = hold;} break;
    case 'e':
    (print != 'E')? (brushc = 1):(brushc = 0); break; 
   
    case 'w': posy--; if(posy < 1){posy = 1;} break;
    case 's': posy++; if(posy > height){posy = height;} break;
    case 'd': posx+=spacing; if(posx > width-1){posx = width - 1;} break;
    case 'a': posx-=spacing; if(posx < 2){posx = 2;} break;

    case 'j': brushc --; break;
    case 'k': brushc ++; break;
    case 'u': brushc -= 2; break;
    case 'i': brushc += 2; break;
    
    case '.': spacing ++; if(spacing>8){spacing = 8;} break;
    case ',': spacing --; if(spacing<1){spacing = 1;} break;
    
    case 'r': 
      posy = height/2;
      posx = width/2;
      wmove(win, posy, posx);
      break;
    case 'Y': clear_canvas(TRUE); break;
    case 't': inputtext(); break;
    case 'b': combrush(); break;

    case '+': savefunc(); break;
    case 'o': askopen(); break;
    case 'q': quitfunc(); break;
    case 'Q': kill_quit(0); break; 
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

int combrush(void){
  mvwprintw(panels,1,1, "COMMAND MODE");
  wrefresh(panels);
  int comnum;
  echo();
  mvwscanw(panelc,2,2, "%u", &comnum);
  noecho();
  comnum+=2;
  if(comnum <= brushnum){
  brushc = comnum;
  }
  wclear(panels);
  wclear(panelc);
  wrefresh(panelc);
  wrefresh(panels);
  return 0;
}


void inputtext(void){
  mvwprintw(panels,1,1, "TEXT MODE");
  wrefresh(panels);
  int storage = 0;

  while(1){
    storage = getch();
    if (storage == '\n'){break;}
    if (storage == KEY_BACKSPACE){
      posx-=spacing;
      mvwaddch(win, posy, posx, ' ');
  *(board + height * (posy-1) + posx-1) = ' ';  
   
    }else{
      mvwaddch(win, posy, posx, storage);
      *(board + height * (posy-1) + posx-1) = storage;  
      posx+=spacing;
    }  
    wrefresh(win);
  }
  wclear(panels);
  wrefresh(panels);

}

void askopen(void){
  int sure; int line;
  char thelineinquestion[128];
  clear();
  printw("What file do you want to open? : ");
  line = showdir("./images/");
  echo();
  mvgetstr(line+1, 0, thelineinquestion);
  noecho();
  sure = openfunc(thelineinquestion);
  if(sure == 1){printw("Sorry, that file doesn't exist");return;}
  for(int e = 0; e < height; e++){
    for(int f = 0; f < width; f++){
      mvwaddch(win, e, f+1, *(board + e*height + f));
    }
  }
  clear();
  refresh();
  wrefresh(win);
  return;
}




void quitfunc(){
  clear();
  printw("Are you sure? (Y)es, (N)o.");
  temp = getch();
  if(temp != 'y'){/*printw(" || %c ||", temp);*/ clear(); refresh(); return;}
  clear();
  refresh();  
   
  for(int e = 1; e<height-1; e++){
    for(int f = 1; f<width-1; f++){
      mvwaddch(stdscr,e, f, *(board + e*height + f));
      if(f == width-1){addch('!');}
    }
  }
mvprintw(0,0,"would you like to save this image ? (Y)es, (N)o, (R)eturn");
  temp = getch();
if(temp != 'y' && temp != 'n'){clear(); refresh(); return;}
if(temp == 'y'){savefunc();}  
  
  delwin(panelb);
  delwin(panelh);
  delwin(win);
  
  kill_quit(0);
}
