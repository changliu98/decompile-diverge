static int utf8_to_unicode(char *in, int inlen, int i, int *utf8len)
{
  int ret = 0;
  if (i < inlen - 1 && (in[i] & 0xe0) == 0xc0 && (in[i + 1] & 0xc0) == 0x80)
  {
    *utf8len = 2;
    ret = (in[i] & 0x1f) * 0x40 + (in[i + 1] & 0x3f);
    if (ret < 0x80)
      return 0;
  }
  else if (i < inlen - 2 && (in[i] & 0xf0) == 0xe0 && (in[i + 1] & 0xc0) == 0x80 && (in[i + 2] & 0xc0) == 0x80)
  {
    *utf8len = 3;
    ret = (in[i] & 0xf) * 0x100 + (in[i + 1] & 0x3f) * 0x40 + (in[i + 2] & 0x3f);
    if (ret < 0x800)
      return 0;
  }
  else if (i < inlen - 3 && (in[i] & 0xf8) == 0xf0 && (in[i + 1] & 0xc0) == 0x80 && (in[i + 2] & 0xc0) == 0x80 && (in[i + 3] & 0xc0) == 0x80)
  {
    *utf8len = 4;
    ret = (in[i] & 0x7) * 0x1000 + (in[i + 1] & 0x3f) * 0x40 + (in[i + 2] & 0x3f) * 0x10 + (in[i + 3] & 0x3f);
    if (ret < 0x10000)
      return 0;
  }
  return ret;
}