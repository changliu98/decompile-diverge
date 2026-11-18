int new_strcpy(char *dest, char *src, int n)
{
  int i;

  i = 0;
  while ((char)(i < src[i] && i < n))
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (0);
}