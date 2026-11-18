#include <stdio.h>

void dummyfunc( char s[] )
{
 int e = 0;
 char ss[] = "Goodbye";

 while( s[ e ] != '\0' )
 {
  s[ e ] = ss[ e ];
  ++e;
 }
}
