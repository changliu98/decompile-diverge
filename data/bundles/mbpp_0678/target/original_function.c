char* func0(char* str1) {
  int i, j = 0;
  int len = strlen(str1);
  for (i = 0; i < len; i++) {
    if (str1[i] != ' ') {
      str1[j++] = str1[i];
    }
  }
  str1[j] = '\0';
  return str1;
}