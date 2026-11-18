int func0(char s[], char c) {
  int res = 0;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == c) {
      res = res + 1;
    }
  }
  return res;
}