int is_multiple(char *str1, char *str2)
{
  int i;
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  if (len1 % len2 != 0)
    return 0;
  for (i = 0; i < len1; i++)
    if (str1[i] != str2[i % len2])
      return 0;
  return 1;
}