#include <stdio.h>

void reverse(char s[])
{
 int i, j;
 char tmp;

 for (i = 0; s[i] != '\0' && s[i] != '\n'; ++i)
  ;

 j = i - 1;
 for (i = 0; i < j; ++i, --j) {
  tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
 }
}
