int func0(char *str)
{
  int count = 0;
  int length = strlen(str);
  int i = 0;
  for (i = 0; i < length; i++)
  {
    if (str[i] == i + 65 || str[i] == i + 97)
    {
      count++;
    }
  }
  return count;
}