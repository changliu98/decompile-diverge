int scan_8long(const char *src, unsigned long *dest) {
  unsigned long l = 0;
  int i = 0;
  unsigned long c;
  while (1) {
    c = src[i] - '0';
    if (c >= 8) break;
    l *= 8;
    l += c;
    i++;
  }
  *dest = l;
  return i;
}