void putoct(char *s, unsigned short n) {
  char *p;
  s[7] = 0;
  s[6] = ' ';
  p = s + 5;
  *p-- = (n & 7) + '0';
  while (p != s) {
    n >>= 3;
    *p-- = (n ? (n & 7) + '0' : ' ');
  }
}