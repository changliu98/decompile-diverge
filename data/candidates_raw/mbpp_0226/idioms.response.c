char *oddeven(char *str)
{
  int i; int j = 0;
  for (i = 0; i < strlen(str); i++)
  {
    if (i % 2 == 0)
    {
      oddeven_result[j++] = str[i];
    }
  }
  oddeven_result[j] = '\0';
  return oddeven_result;
}