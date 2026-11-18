void reverse(char *str)
{
  int len = 0;
  char *p = str;
  char tmp;
  int i;
  for (p = str; *p != '\0'; p++)
    len++;
  for (i = 0; i <= (len / 2) - 1; i++)
  {
    tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  }
}