void reverse(char *str)
{
  unsigned int i; unsigned int j;
  char tmp;
  for (i = 0; str[i]; i++)
    ;
  j = i;
  for (i = 0; i < j / 2; i++)
  {
    tmp = str[i];
    str[i] = str[j - (i + 1)];
    str[j - (i + 1)] = tmp;
  }
}