char *scnline(int c, char *p, int f) {
  int i;
  char ch;
  i = 8;
  while (--i) {
    c <<= 1;
    if (c & 0x80)
      ch = f;
    else
      ch = ' ';
    *p++ = ch;
  }
  return p;
}