static void int2str(int n, int base, char *buf) {
  char *p, tmp;
  p = buf;
  while (n) {
    *p++ = "0123456789abcdefghijklmnopqrstuvwxyz"[n % base];
    n /= base;
  }
}