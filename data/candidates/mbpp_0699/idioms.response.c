int func0(char *str1, char *str2)
{
  int i;
  int count = 0;
  int length = strlen(str1);
  for (i = 0; i < length; i++)
  {
    if (str1[i] != str2[i])
    {
      count++;
    }
  }
  if (count % 2 == 0)
  {
    return count / 2;
  }
  else
  {
    return -1;
  }
}