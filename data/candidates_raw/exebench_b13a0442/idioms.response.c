void reverse(char *str)
{
  int i = 0;
  int j = 0;
  char temp;
  for (i = 0; str[i] != '\0'; i++)
  {
  }
  i = i - 1;
  for (j = 0; j < i; j++)
  {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i--;
  }
}