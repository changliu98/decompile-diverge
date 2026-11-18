char **filter(char **str, int n, int l, int *size)
{
  int i; int count = 0;
  for (i = 0; i < n; i++)
    if (strlen(str[i]) == l)
      result[count++] = str[i];
  *size = count;
  return result;
}