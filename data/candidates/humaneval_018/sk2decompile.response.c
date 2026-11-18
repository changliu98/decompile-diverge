int func0(char *s, char *t) {
  int i, n, m, c = 0;
  n = strlen(s);
  m = strlen(t);
  if (n == 0) return 0;
  for (i = 0; i <= n - m; i++) {
    if (!strncmp(s + i, t, m)) c++;
  }
  return c;
}