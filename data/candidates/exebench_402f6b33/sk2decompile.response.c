void itoa(int n, char *s, int base) {
  int sign = n;
  int i;
  char tmp[16];
  int j;
  if (n < 0) n = -n;
  j = 0;
  if (n == 0)
    tmp[j++] = '0';
  else
    while (n) {
      tmp[j++] = "0123456789ABCDEF"[n % base];
      n /= base;
    }
  if (sign < 0) tmp[j++] = '-';
  while (j--) *s++ = tmp[j];
  *s = '\0';
}