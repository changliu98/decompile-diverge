int func0(char *str) {
  int len, i, count = 0, n;
  n = strlen(str);
  for (i = 0; i < n; i++) {
    for (len = 1; len <= n - i; len++) {
      if (check_Equality(str, i, len)) count++;
    }
  }
  return count;
}