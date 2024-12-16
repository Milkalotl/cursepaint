#ifndef CURSEPAINT_H
#define CURSEPAINT_H
extern char temp;
extern int height;
extern int width;
extern char * board;


void  ptswin(void);
void  ptspanel(void);
int   combrush(void);
void  inputtext(void);
char  inputmove(void);
void  askopen(void);
void  quitfunc(void);

#endif
