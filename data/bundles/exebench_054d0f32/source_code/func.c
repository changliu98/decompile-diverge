#include <stdlib.h>

char *my_strupcase(char *str)
{
  int lp;

  if (str == NULL)
    return (NULL);
  lp = 0;
  while (str[lp] != '\0')
    {
      if (str[lp] >= 97 && str[lp] <= 122)
 str[lp] -= 32;
      ++lp;
    }
  return (str);
}
