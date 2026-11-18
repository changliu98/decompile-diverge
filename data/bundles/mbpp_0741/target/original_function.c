bool func0(const char *s) {
  int n = strlen(s);
  for (int i = 1; i < n; i++) {
    if (s[i] != s[0]) {
      return false;
    }
  }
  return true;
}