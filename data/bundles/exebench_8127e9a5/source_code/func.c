#include <stdio.h>

#include <stdlib.h>

void reverse(char *str)
{
  size_t str_len = 0;
  size_t i, j;
  char tmp;

  while (str[str_len] != '\0') str_len++;

  if (str_len > 0) {
    i = 0;
    j = str_len - 1;
    while (i < j) {
      tmp = str[i];
      str[i] = str[j];
      str[j] = tmp;
      i++;
      j--;
    }
  }
}
