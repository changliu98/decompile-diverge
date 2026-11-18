char *strcpy(char *dest, char *src)
{
  int i = 0;
  while(src[i++] != '\0')
    dest[i - 1] = src[i - 1];
  return dest;
}