char *func0(char *str1, char *str2)
{
  int i;
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int len;
  char *hamming = ((void *)0);
  if (len1 < len2)
    len = len1;
  else
    len = len2;
  hamming = (char *)malloc((len + 1) * sizeof(char));
  if (hamming == ((void *)0))
    return ((void *)0);
  for (i = 0; i < len; i++)
    hamming[i] = (str1[i] == str2[i]) ? '1' : '0';
  hamming[len] = '\0';
  return hamming;
}