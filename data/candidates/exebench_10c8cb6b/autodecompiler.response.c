char *stringCopy(char *dest, char *src)
{
  while ((*dest = *src) != '\0')
    {
      dest++;
      src++;
    }
  return (dest);
}