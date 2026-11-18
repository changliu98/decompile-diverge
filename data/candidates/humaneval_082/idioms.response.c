int func0(char *str)
{
  int len = strlen(str);
  int i;
  if (len < 2)
    return 0;
  for (i = 2; i * i <= len; i++)
    if (len % i == 0)
      return 0;
  return 1;
}