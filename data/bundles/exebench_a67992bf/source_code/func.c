#include <sys/types.h>

#include <stdio.h>

size_t itoa(char *str, int i)
{
 unsigned int u;
 char tmp[(sizeof("-2147483648") - 1) + 1];
 char *end = tmp + sizeof(tmp);
 char *p = end - 1;
 char *s = str;

 u = (i < 0) ? -i : i;

 do {
  *p-- = '0' + (u % 10);
  u /= 10;
 } while (u != 0);

 if (i < 0)
  *p = '-';
 else
  p++;

 for (; p < end; p++)
  *s++ = *p;

 *s = '\0';

 return (size_t)(s - str);
}
