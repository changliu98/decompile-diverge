char zhalfstr(char *s) {
  char c, c1, c2;
  int i, n, k;
  c2 = '0';
  c1 = '0';
  i = -1;
  n = 0;
  k = 0;
  while (c2 != '\0') {
    c = s[i + 1];
    s[i - k + 1] = '0' + (c2 & 1) * 5 + (c - '0') / 2;
    if (s[i - k + 1] != '0' || n)
      n = 1;
    else
      k++;
    c1 = c2;
    c2 = c;
    i++;
  }
  if (i == k) {
    s[0] = '0';
    s[1] = '\0';
  } else
    s[i - k] = '\0';
  return c1;
}