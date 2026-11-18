int do_map(char *out, int map, int in)
{
  switch (in) {
  case '\n':
    if (map & 0x0008) {
      *out = '\r';
      return 1;
    }
    if (map & 0x0010) {
      *out = '\r';
      out++;
      *out = '\n';
      return 2;
    }
    if (map & 0x0020)
      return 0;
    *out = in;
    return 1;
  case '\r':
    if (map & 0x0001) {
      *out = '\n';
      return 1;
    }
    if (map & 0x0002) {
      *out = '\r';
      out++;
      *out = '\n';
      return 2;
    }
    if (map & 0x0004)
      return 0;
    *out = in;
    return 1;
  case '\b':
    if (map & 0x0080)
      *out = 0x7f;
    else
      *out = in;
    return 1;
  case 0x7f:
    if (map & 0x0040)
      *out = '\b';
    else
      *out = in;
    return 1;
  default:
    *out = in;
    return 1;
  }
}