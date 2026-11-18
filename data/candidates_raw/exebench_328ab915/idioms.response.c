int utf8encode(char *out, int in)
{
  if (in < 128)
  {
    *out = in & 0xff;
    return 1;
  }
  if (in < 2048)
  {
    *out = 0xc0 + (in >> 6);
    out++;
    *out = 0x80 + (in & 0x3f);
    return 2;
  }
  if (in < 0x10000)
  {
    *out = 0xe0 + (in >> 12);
    out++;
    *out = 0x80 + ((in >> 6) & 0x3f);
    out++;
    *out = 0x80 + (in & 0x3f);
    return 3;
  }
  if (in < 0x110000)
  {
    *out = 0xf0 + (in >> 18);
    out++;
    *out = 0x80 + ((in >> 12) & 0x3f);
    out++;
    *out = 0x80 + ((in >> 6) & 0x3f);
    out++;
    *out = 0x80 + (in & 0x3f);
    return 4;
  }
  in = 0xfffd;
  *out = 0xf0 + (in >> 18);
  out++;
  *out = 0x80 + ((in >> 12) & 0x3f);
  out++;
  *out = 0x80 + ((in >> 6) & 0x3f);
  out++;
  *out = 0x80 + (in & 0x3f);
  return 4;
}