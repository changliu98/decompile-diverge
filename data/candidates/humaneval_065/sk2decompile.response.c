char *func0(int n, int k) {
  static char s[50];
  char t[50];
  char c;
  int l, i;
  sprintf(s, "%d", n);
  l = strlen(s);
  if (l < k) {
    for (i = 0; i < l / 2; i++) {
      c = s[i];
      s[i] = s[l - 1 - i];
      s[l - 1 - i] = c;
    }
  } else {
    strcpy(t, s + l - k);
    t[k] = '\0';
    strncat(t, s, l - k);
    strcpy(s, t);
  }
  return s;
}