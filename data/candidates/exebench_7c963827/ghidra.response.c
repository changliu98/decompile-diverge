size_t scan_ulong(char *s,unsigned_long *l)

{
  uint digit;
  unsigned_long x;
  size_t n;
  unsigned_long *l_local;
  char *s_local;
  
  n = 0;
  x = 0;
  while ((int)s[n] - 0x30U < 10) {
    x = x * 10 + (ulong)((int)s[n] - 0x30U);
    n = n + 1;
  }
  *l = x;
  return n;
}