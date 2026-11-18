int utf8_to_unicode(char *in, unsigned long len, unsigned int *out)
{
  unsigned char c = *in;
  if (len == 0)
    return 0;
  if (c < 0x80)
  {
    *out = c & 0xff;
    return 1;
  }
  if ((c & 0xe0) == 0xc0 && len >= 2)
  {
    *out = (c & 0x1f) << 6 | (in[1] & 0x3f);
    return 2;
  }
  if ((c & 0xf0) == 0xe0 && len >= 3)
  {
    *out = (c & 0x0f) << 12 | (in[1] & 0x3f) << 6 | (in[2] & 0x3f);
    return 3;
  }
  if ((c & 0xf8) == 0xf0 && len >= 4)
  {
    *out = (c & 0x07) << 18 | (in[1] & 0x3f) << 12 | (in[2] & 0x3f) << 6 | (in[3] & 0x3f);
    return 4;
  }
  return 0;
}