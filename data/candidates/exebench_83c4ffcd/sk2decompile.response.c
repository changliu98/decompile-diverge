char *copy_line(char *dest, char *src, int maxlen) {
  int i;
  for (i = 0; i < maxlen - 1 && *src && *src != '\n' && *src != '\r'; i++)
    *dest++ = *src++;
  *dest = '\0';
  if (*src == '\r') src++;
  if (*src == '\n') src++;
  return src;
}