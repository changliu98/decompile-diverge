#include <stdio.h>

void right_shift_str( char *p ,int n)
{
 int i ,j;
 int length_of_str = 0;
 char *q = p;
 char temp;


 while( '\0' != *q )
 {
  length_of_str++;
  q++;
 }

 for( j = 0; j < n; j++ )
 {

  temp = *(p + (length_of_str - 1) );
  for ( i = length_of_str-1 ; i > 0 ; i-- )
  {
   p[i] =p[i-1];
  }
  p[0] = temp;
 }
}
