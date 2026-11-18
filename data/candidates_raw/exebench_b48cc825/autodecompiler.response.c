char *strcpy(char *dest, const char *src)
{
  int c;
  char *ret = dest;

  do {
    c = *dest++ = *src++;
  } while (c);

  return ret;
}