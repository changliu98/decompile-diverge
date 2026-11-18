void Reverse(char *str)
{
  int i = 0; int j = 0;
  char temp;
  for (i = 0; str[i] != '\0'; i++)
    ;
  i = i - 1;
  if (str[i] == '\n')
    i = i - 1;
  for (j = 0; j < i; j++, i--)
  {
    temp = str[j];
    str[j] = str[i];
    str[i] = temp;
  }
}