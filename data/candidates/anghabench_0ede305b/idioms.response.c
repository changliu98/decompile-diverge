static enum fons_utf8d fons__decutf8(enum fons_utf8d *st, unsigned int *codep, unsigned int byte)
{
  enum fons_utf8d type = fons__decutf8_utf8d[byte];
  unsigned int tmp;
  if (*st == FONS_UTF8_ACCEPT)
    tmp = (byte & (0xff >> type));
  else
    tmp = (*codep << 6) | (byte & 0x3f);
  *codep = tmp;
  *st = fons__decutf8_utf8d[(type + 0x100) + *st];
  return *st;
}