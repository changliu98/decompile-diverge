static unsigned long rtrim(char *str, unsigned long len)
{
  char c;
  while (len > 0) {
    c = str[len - 1];
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
      str[--len] = '\0';
    else
      break;
  }
  return len;
}