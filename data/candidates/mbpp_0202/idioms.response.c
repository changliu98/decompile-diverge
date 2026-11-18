char *func0(char *str1)
{
  int i = 0; int j = 1;
  for (i = 0; i < strlen(str1); i++)
  {
    if (j % 2 == 1)
    {
      str2[i] = str1[strlen(str1)-j];
    }
    j++;
  }
  str2[i] = '\0';
  return str2;
}