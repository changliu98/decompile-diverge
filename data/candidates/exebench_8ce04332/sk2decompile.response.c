void int2str(int n, int base, char *s) {
  while (base) {
    *s++ = '0' + n / base % 10;
    base /= 10;
  }
}