void reverse(char *str)
{
  int i; int j;
  int len;
  char tmp;
  for (i = 0; str[i] != '\0'; i++)
  {
  }
  len = i;
  for (i = 0; i < len / 2; i++)
  {
    tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  }
}