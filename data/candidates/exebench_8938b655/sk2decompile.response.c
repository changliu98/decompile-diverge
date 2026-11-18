int itos(int n, char *s) {
  int i, j, k, l, m;
  char c;
  i = n;
  if (i < 0) {
    j = 0;
    i = -i;
    k = 1;
    s[0] = '-';
  } else {
    j = -1;
    k = 0;
  }
  do {
    l = i % 10;
    i /= 10;
    j++;
    s[j] = l + '0';
  } while (i != 0);
  s[j + 1] = '\0';
  m = j + 1;
  for (j = k; j < k + m - 1; j++, m--) {
    c = s[j];
    s[j] = s[m - 1];
    s[m - 1] = c;
  }
  return m;
}