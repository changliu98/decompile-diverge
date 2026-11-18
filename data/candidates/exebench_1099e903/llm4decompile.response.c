void set_nb(char *str, char sep, int *nb)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      if (i == j && str[i] == sep)
 {
   ++i;
   ++j;
 }
      else if (str[j] == sep || str[j] == '\0')
 {
   ++(*nb);
   i = j;
 }
      else
 ++j;
    }
}