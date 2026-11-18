char *my_strncpy(char *dest, char *src, int n)
{
  int i;
  for (i = 0; (src[i] != '\0') || (i < n); i++)
    if (i < n)
      dest[i] = src[i];
    else
      dest[i] = '\0';
  return dest;
}