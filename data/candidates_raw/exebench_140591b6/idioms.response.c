void unescape(char *dest, char *src, int destsize)
{
  char c;
  int canput;
  while (1) {
    canput = 0;
    if (*src)
      canput = (destsize > 1);
    if (!canput)
      break;
    if (*src == '\\' && *(++src) == 'n')
      c = '\n';
    else
      c = *src;
    *dest++ = c;
    ++src;
    --destsize;
  }
  *dest = '\0';
}