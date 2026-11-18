#include <sys/types.h>

#include <sys/uio.h>

#include <stdlib.h> /* realloc, rand ... */

#include <stdio.h>

#include <unistd.h>

#include <errno.h>

#include <ctype.h> /* isprint */

#include <time.h> /* time */

static char* parse_fmt(char* fmt, int* type, int* size)
{
 char* s;

 s=fmt;
 do{
  for(;*fmt && *fmt!='%'; fmt++);
  if (*fmt=='%'){
   switch(*(fmt+1)){
    case 'v':
     *type=0xf;
     *size=(int)(fmt-s);
     return (fmt+2);
     break;
    case '%':

     *size=(int)(fmt-s)+1;
     *type=-1;
     return (fmt+2);
     break;
   }
  }
 }while(*fmt);
 *type=-1;
 *size=(fmt-s);
 return fmt;
}
