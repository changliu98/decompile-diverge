int func0(char *str, char c)
{
  int count = 0;
  int i;
  for (i = 0; i < strlen(str); i++)
  {
    if (str[i] == c)
    {
      count++;
    }
  }
  return (count);
}