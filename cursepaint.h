#ifndef CURSEPAINT_H
#define CURSEPAINT_H
extern char temp;
extern int height;
extern int width;
extern char * board;

void win_attrons(void);
void clear_canvas(bool is_window_active);
void kill_quit(int condition);
void border_print_once(void);
void  brush_functionality(void);
void  ptspanel(void);
int   combrush(void);
void  inputtext(void);
char  inputmove(void);
void  askopen(void);
void  quitfunc(void);

#endif
