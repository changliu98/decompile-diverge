char *func0(char *str)
{
  int i; int j = 0;
  for (i = 0; str[i]; i++)
    if (str[i] >= 'a' && str[i] <= 'z')
      strlower_result[j++] = str[i];
  strlower_result[j] = '\0';
  return strlower_result;
}