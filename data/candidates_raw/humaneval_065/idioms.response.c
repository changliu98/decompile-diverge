char *strrotl(int x, int shift)
{
  int i;
  int len;
  int temp;
  char tempstr[50];
  char tempchar;
  char *str = func0_xs;
  sprintf(str,"%d",x);
  len = strlen(str);
  if (len < shift)
  {
    for (i = 0; i < len / 2; i++)
    {
      temp = str[i];
      str[i] = str[len - 1 - i];
      str[len - 1 - i] = temp;
    }
  }
  else
  {
    strcpy(tempstr, &str[len - shift]);
    tempstr[shift] = '\0';
    strncat(tempstr, str, len - shift);
    strcpy(str, tempstr);
  }
  return str;
}