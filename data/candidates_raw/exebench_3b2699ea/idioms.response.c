void reverse(char *str)
{
  int i;
  int len = 0;
  char tmp;
  while (str[len])
    len++;
  for (i = 0; i < len / 2; i++)
    {
      tmp = str[i];
      str[i] = str[len - i - 1];
      str[len - i - 1] = tmp;
    }
}