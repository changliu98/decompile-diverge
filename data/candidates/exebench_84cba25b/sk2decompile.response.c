static char *base91(char *p, int v) {
  *p++ = v / 91 + 33;
  *p++ = v % 91 + 33;
  return p;
}