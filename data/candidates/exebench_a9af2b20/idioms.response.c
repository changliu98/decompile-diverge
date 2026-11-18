char *stpCpy(char *dest, char *src)
{
  char *d = dest;
  for (;;) {
    char c = *src++;
    if (c == '\0')
      break;
    *d = c;
    d++;
  }
  return dest;
}