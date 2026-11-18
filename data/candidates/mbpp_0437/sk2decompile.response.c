char *func0(char *str) {
  static char str1[100];
  int i, j = 0;
  for (i = 1; i <= strlen(str); i++) {
    if (i % 2 == 0) {
      str1[j++] = str[i - 1];
    }
  }
  str1[j] = '\0';
  return str1;
}