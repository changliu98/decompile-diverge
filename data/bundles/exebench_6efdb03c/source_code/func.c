#include <stdio.h>

#include <stdlib.h>

void rev(char *s)
{
  int l = 0;
  while (s[l])
    l++;

  char b;
  for (int i = 0; i < l / 2; i++)
    b = s[i], s[i] = s[l - i - 1], s[l - i - 1] = b;
}
