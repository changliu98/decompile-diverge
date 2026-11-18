void leftrot(char *str, int n)
{
  int i; int j; int len = 0;
  char temp;
  char *ptr = str;
  while(*ptr != '\0')
  {
    len++;
    ptr++;
  }
  for(j = 0; j < n; j++)
  {
    temp = str[len-1];
    for(i = len-1; i > 0; i--)
    {
      str[i] = str[i-1];
    }
    str[0] = temp;
  }
}