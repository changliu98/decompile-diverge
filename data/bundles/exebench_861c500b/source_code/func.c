#include <ctype.h>

#include <stdlib.h>

#include <sys/queue.h>

#include <string.h>

#include <assert.h>

#include <stdio.h>

static char *fix(char *d, char *s) {
 int i = 0;
 int di = 0;

 while(s[i]) {
  if( s[i] == '\b' ) {
   --di;
   if(di<0) {
    di = 0;
   }
  } else {
   d[di++] = s[i];
  }
  i++;
 }
 d[di] = '\0';
 return &d[0];
}
