int util_read_dec(const char *str, int *val) {
  const char *p = str;
  int neg = 0;
  int len = 0;
  *val = 0;
  if (*p == '-') {
    neg = 1;
    p++;
    len++;
  }
  while (*p) {
    int digit = *p - '0';
    if (digit < 0 || digit > 9) break;
    *val = *val * 10 + digit;
    if (*val > 2147483647) break;
    p++;
    len++;
  }
  if (neg) {
    if (len == 1) return 0;
    *val = -*val;
  }
  return len;
}