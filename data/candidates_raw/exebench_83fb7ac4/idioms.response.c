char *strcpy(char *dest, char *src)
{
  char c;
  while ( (c = *src) != '\0') {
    *dest = c;
    dest++;
    src++;
  }
  return dest;
}