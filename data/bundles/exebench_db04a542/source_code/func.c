#include <math.h> // floor()

#include <stdio.h>

#include <stdlib.h>

#include <sys/stat.h> // cache purposes [Ind/Hercules]

static char *checkpath(char *path, const char *srcpath)
{

 char *p=path;

 if((void *)0!=path && (void *)0!=srcpath) {
  while(*srcpath) {
   if (*srcpath=='\\') {
    *p++ = '/';
    srcpath++;
   }
   else
    *p++ = *srcpath++;
  }
  *p = *srcpath;
 }
 return path;
}
