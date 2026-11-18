int unicode_to_utf8(char *s, int c)
{
  char *t = s;
  if (c < 0x80)
    *t++ = c;
  else if (c < 0x800)
    *t++ = 0xc0 | (c >> 6), *t++ = 0x80 | (c & 0x3f);
  else if (c < 0x10000)
    *t++ = 0xe0 | (c >> 12), *t++ = 0x80 | ((c >> 6) & 0x3f), *t++ = 0x80 | (c & 0x3f);
  else if (c < 0x200000)
    *t++ = 0xf0 | (c >> 18), *t++ = 0x80 | ((c >> 12) & 0x3f), *t++ = 0x80 | ((c >> 6) & 0x3f), *t++ = 0x80 | (c & 0x3f);
  else if (c < 0x4000000)
    *t++ = 0xf8 | (c >> 24), *t++ = 0x80 | ((c >> 18) & 0x3f), *t++ = 0x80 | ((c >> 12) & 0x3f), *t++ = 0x80 | ((c >> 6) & 0x3f), *t++ = 0x80 | (c & 0x3f);
  else
    *t++ = 0xfc | (c >> 30), *t++ = 0x80 | ((c >> 24) & 0x3f), *t++ = 0x80 | ((c >> 18) & 0x3f), *t++ = 0x80 | ((c >> 12) & 0x3f), *t++ = 0x80 | ((c >> 6) & 0x3f), *t++ = 0x80 | (c & 0x3f);
  *t = '\0';
  return t - s;
}