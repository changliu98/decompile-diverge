#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <errno.h>

#include <assert.h>

#include <stdarg.h>

#include <signal.h>

#include <unistd.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/wait.h>

#include <limits.h>

#include <getopt.h>

int
do_map (char *b, int map, char c)
{
 int n;

 switch (c) {
 case '\x7f':

  if ( map & (1 << 6) ) {
   b[0] = '\x08'; n = 1;
  } else {
   b[0] = c; n = 1;
  }
  break;
 case '\x08':

  if ( map & (1 << 7) ) {
   b[0] = '\x7f'; n = 1;
  } else {
   b[0] = c; n = 1;
  }
  break;
 case '\x0d':

  if ( map & (1 << 0) ) {
   b[0] = '\x0a'; n = 1;
  } else if ( map & (1 << 1) ) {
   b[0] = '\x0d'; b[1] = '\x0a'; n = 2;
  } else if ( map & (1 << 2) ) {
   n = 0;
  } else {
   b[0] = c; n = 1;
  }
  break;
 case '\x0a':

  if ( map & (1 << 3) ) {
   b[0] = '\x0d'; n = 1;
  } else if ( map & (1 << 4) ) {
   b[0] = '\x0d'; b[1] = '\x0a'; n = 2;
  } else if ( map & (1 << 5) ) {
   n = 0;
  } else {
   b[0] = c; n = 1;
  }
  break;
 default:
  b[0] = c; n = 1;
  break;
 }

 return n;
}
