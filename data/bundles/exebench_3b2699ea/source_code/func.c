#include <stdio.h>

void reverse(char str[])
{

 int i,len;
 char c;

 for(len=0; str[len]; len++) ;

 for(i=0; i<len/2; i++)
 {
  c = str[i];
  str[i] = str[len-i-1];
  str[len-i-1] = c;
 }
}
