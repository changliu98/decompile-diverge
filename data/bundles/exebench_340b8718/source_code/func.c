#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <errno.h>

#include <ctype.h>

#include <time.h>

#include <fcntl.h>

char *strtoupper( char *s ){
 int i, len = sizeof(s);
 for( i = 0; i < len; i++ ){
  s[i] = ( s[i] >= 'a' && s[i] <= 'z' ? s[i] + 'A' - 'a' : s[i] );
 }
 return(s);
}
