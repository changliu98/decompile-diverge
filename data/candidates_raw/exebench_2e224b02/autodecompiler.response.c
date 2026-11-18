void print_hex(long n, char *buf) {
  char hex[9];
  hex[0] = '\0';
  int i = 1;
  while (1) {
    if (i > 8) break;
    hex[i] = "0123456789abcdef"[n & 0xf];
    n >>= 4;
    ++i;
  }
  i = 8;
  while (1) {
    if (hex[i] == '0') --i;
    else break;
  }
  if (i == 0) ++i;
  while (1) {
    if (i < 1) return;
    *buf++ = hex[i--];
  }
}