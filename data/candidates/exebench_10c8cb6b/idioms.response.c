char *stringCopy(char *dst, char *src)
{
  char c;
  while ((c = *src) != '\0') {
    *dst = c;
    dst++;
    src++;
  }
  return (dst);
}