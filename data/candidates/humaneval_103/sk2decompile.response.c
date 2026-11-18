char *func0(int l, int r) {
  if (l > r) {
    return "0";
  }
  int m = (l + r) / 2;
  char *s = malloc(33);
  s[0] = '\0';
  int i = 32;
  s[32] = '\0';
  do {
    s[i--] = m % 2 + '0';
    m /= 2;
  } while (m > 0);
  return s + i + 1;
}