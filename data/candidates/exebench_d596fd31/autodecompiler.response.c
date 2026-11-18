size_t itoa(unsigned int value, char *str, unsigned int radix)
{
  char tmp[33];
  char *tp = tmp;
  size_t i;
  size_t len;
  const char *vowels = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned int v;

  if (radix < 2 || radix > 36) {
    return 0;
  }

  if (value == 0) {
    str[0] = '0';
    return 1;
  }

  v = value;

  while (v) {
    int c = v % radix;
    v /= radix;
    *tp++ = vowels[c];
  }

  for (len = (tp - tmp), i = 0; i < len; ++i) {
    str[i] = tmp[len - 1 - i];
  }

  return i;
}