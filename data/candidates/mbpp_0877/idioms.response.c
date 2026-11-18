void func0(char *str)
{
  int i; int j;
  int len = strlen(str);
  char temp;
  for (i = 0; i < len - 1; i++)
  {
    for (j = i + 1; j < len; j++)
    {
      if (str[i] > str[j])
      {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }
}