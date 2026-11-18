void utf8_int_string(unsigned int u, char *s)
{
  if (s == ((void *)0))
    return;
  s[0] = 0;
  if (u <= 0x7f)
  {
    s[0] = (char) u;
    s[1] = 0;
  }
  else if (u <= 0x7ff)
  {
    s[0] = (char) (0xc0 | ((u & 0x7f0) >> 6));
    s[1] = (char) (0x80 | ( u & 0x03f));
    s[2] = 0;
  }
  else if (u <= 0xffff)
  {
    s[0] = (char) (0xe0 | ((u & 0xf000) >> 12));
    s[1] = (char) (0x80 | ((u & 0x0fc0) >> 6));
    s[2] = (char) (0x80 | ( u & 0x03f));
    s[3] = 0;
  }
  else if (u <= 0x1fffff)
  {
    s[0] = (char) (0xf0 | ((u & 0x1c0000) >> 18));
    s[1] = (char) (0x80 | ((u & 0x03f000) >> 12));
    s[2] = (char) (0x80 | ((u & 0x0fc0) >> 6));
    s[3] = (char) (0x80 | ( u & 0x03f));
    s[4] = 0;
  }
}