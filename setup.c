#include <ncurses.h>
#include <stdlib.h>

#include "cursepaint.h"

int setup(){
 // int mhold;
  WINDOW * setupwin;  
//  int holdwidth;
//  int holdheight;
  setupwin = newwin(LINES/2, COLS/2, LINES/4, COLS/4);
  wborder(setupwin, '|','|','-','-','+','+','+','+'); 
  wrefresh(setupwin);
  /*
  wprintw(setupwin"Would you like to:\n - Work with a custom size (-1)\n - Work with adaptive size (1)\n: ");
  scanf("%d", &mhold);
  if(mhold != -1){
    height = LINES/2;
    width = COLS/2;

  }else

  do{
    wprintw("\nPlease specify the desired width and height for the canvas\nHeight: ");
    getint("%d", &height);
    wprintw("\nWidth: ");
    scanf("%d", &width);
    wprintw("\nAre you sure of your choices? Height: %d / Width: %d\n Type -1 for changes, type 1 to start CURSEPAINT\n: ", height, width);
    scanf("%d", &mhold);
    if(width >= 1000 || height >= 1000 || width <= 0 || height <= 0){ wprintw("\nSorry, please try again. One of your inputted values caused an error.\n "); mhold = -1;}
  }while(mhold == -1);
  */
  height = LINES/2;
  width = COLS/2;

  board = (char *)malloc(height*width * sizeof(char));
  return 0;
}

