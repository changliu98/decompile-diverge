static size_t scan_ulong(const char *str, unsigned long *out) {
  size_t i = 0;
  unsigned long n = 0;
  int digit;
  while ((digit = str[i] - '0') < 10) {
    n = n * 10 + digit;
    i++;
  }
  *out = n;
  return i;
}