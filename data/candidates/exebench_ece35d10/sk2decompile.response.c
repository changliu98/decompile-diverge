char *itoa(int value, char *string, int base) {
  const char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *wstr, *wstr1, tmp;
  int n = value;
  wstr = string;
  wstr1 = string;
  if (wstr == NULL || base < 2 || base > 36) return wstr;
  if (base != 10 && n < 0) return wstr;
  if (n == 0) {
    *wstr++ = '0';
    *wstr = '\0';
    return wstr;
  }
  if (base == 10 && n < 0) {
    *wstr++ = '-';
    n = -n;
  }
  while (n != 0) {
    *wstr++ = num[n % base];
    n /= base;
  }
  *wstr = '\0';
  wstr--;
  while (wstr1 < wstr) {
    tmp = *wstr1;
    *wstr1 = *wstr;
    *wstr = tmp;
    wstr1++;
    wstr--;
  }
  return string;
}