#ifndef CURSEPAINT_H
#define CURSEPAINT_H
extern char temp;
extern int height;
extern int length;
extern char board[33][49];


void  ptswin(void);
void  ptspanel(void);
int   combrush(void);
void  inputtext(void);
char  inputmove(void);
void  askopen(void);
void  quitfunc(void);

#endif
