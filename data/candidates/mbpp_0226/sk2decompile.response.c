char *func0(char *str) {
  int i, j = 0;
  for (i = 0; i < strlen(str); i++) {
    if (i % 2 == 0) {
      str1[j++] = str[i];
    }
  }
  str1[j] = '\0';
  return str1;
}