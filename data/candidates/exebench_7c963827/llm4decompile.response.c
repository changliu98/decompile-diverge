size_t
scan_ulong(const char* src, unsigned long int* dest) {
  register const char *s = src;
  register unsigned long int l = 0;
  register int c;
  size_t n = 0;
  while ((c = (int)(unsigned char)(*s++)) >= '0' && c <= '9') {
    l *= 10;
    l += c - '0';
    n++;
  }
  *dest = l;
  return n;
}