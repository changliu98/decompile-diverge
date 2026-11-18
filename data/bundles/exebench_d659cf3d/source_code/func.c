#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <stdio.h>

#include <errno.h>

#include <sys/file.h>

#include <unistd.h>

#include <time.h>

#include <stdlib.h>

int tt_unesc(char* s, char esc){
  char* src = s;
  char* dst = NULL;
  int n = 0;

  while( *src != esc){
    if(0x0 == *src)
      return 0;
    ++src;
  }

  dst = src;
  while( 0x0 != *src){
    if( *src == esc){
      ++src;
      ++n;
    }
    *dst = *src;
    ++dst;
    ++src;
  }
  return n;
}
