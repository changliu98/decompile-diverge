int utf8_encode(unsigned int u, char *out)
{
  char *p = out;
  int len = 0;
  if (u < 0x80) {
    *p++ = (char)u;
    len = 1;
  }
  else if (u < 0x800) {
    *p++ = (char)(0xc0 | (u >> 6));
    *p++ = (char)(0x80 | (u & 0x3f));
    len = 2;
  }
  else if (u < 0x10000) {
    *p++ = (char)(0xe0 | (u >> 12));
    *p++ = (char)(0x80 | ((u >> 6) & 0x3f));
    *p++ = (char)(0x80 | (u & 0x3f));
    len = 3;
  }
  *p = '\0';
  return len;
}