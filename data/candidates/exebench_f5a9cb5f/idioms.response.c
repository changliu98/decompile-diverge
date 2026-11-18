void reverse(char *str)
{
  int i; int j;
  char tmp;
  for (i = 0; str[i]; i++)
    ;
  for (i = 0, j = i + i; i < j; i++)
    {
      tmp = str[i];
      str[i] = str[j - i];
      str[j - i] = tmp;
    }
}