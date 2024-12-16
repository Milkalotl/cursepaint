#ifndef FILEIO_H
#define FILEIO_H

extern char savename[128];
extern char curdir[128];

int showdir(char* givendir);
int savefunc(void);
int truesave(void);
int openfunc(char* filename);
#endif
