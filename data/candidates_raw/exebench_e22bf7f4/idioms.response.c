void reverse(char *str)
{
  int i = 0;
  int len = 0;
  char tmp;
  while(str[i++])
    len++;
  for(i = 0; i < len / 2; i++)
  {
    tmp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = tmp;
  }
}