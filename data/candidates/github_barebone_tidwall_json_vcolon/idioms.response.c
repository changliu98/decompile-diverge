static int vcolon(unsigned char *json, long len, long i)
{
  int c;
  if (i == len)
    return - (i + 1);
  if (json[i] == ':')
    return i + 1;
  for (;;) {
    c = json[i];
    if (c < ' ' || c == '\r' || c == ' ') {
      if (++i >= len)
        return - (i + 1);
    } else if (c == ':')
      return i + 1;
    else
      return - (i + 1);
  }
}