int sprint_int_number_nonlocalized(char *buf, int n, int min_digits,
                                   int show_sign) {
  int found = 0;
  int pos = 0;
  int div = 1000000000;
  int i;
  int digit;
  if (min_digits < 0) min_digits = 0;
  if (min_digits > 9) found = 1;
  if (n < 0) {
    pos = 1;
    buf[0] = '-';
    n = -n;
  } else if (show_sign) {
    pos = 1;
    buf[0] = '+';
  }
  for (i = 10; i; i--) {
    if (min_digits == i) found = 1;
    digit = n / div;
    n %= div;
    if (digit || found) {
      buf[pos++] = '0' + digit;
      found = 1;
    }
    div /= 10;
  }
  if (!found) buf[pos++] = '0';
  buf[pos] = 0;
  return pos;
}