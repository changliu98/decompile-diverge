int func0(char *str)
{
  int len = strlen(str);
  int i;
  for (i = 1; i < len; i++)
    if (str[i] != str[0])
      return 0;
  return 1;
}